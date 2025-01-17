#include "videoplayer.h"
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QThread>
#include <QDir>
#include <QQueue>
#include <QMessageBox>

static struct SwsContext *img_convert_ctx = nullptr;    // 转换格式上下文

VideoPlayer::VideoPlayer()
{
    qDebug() << "version: " << av_version_info();
    qDebug() <<  avcodec_version();
    m_pause_flag = false;
    m_record_flag = false;


    if(videoPlayer_init() < 0) {
        emit errorOccurred(tr("videoPlayer_init error."));
        return;
    }

    if(initOutput("video.mp4") < 0) {
        emit errorOccurred(tr("initOutput error."));
        return;
    }

    threadIndex = 0;
    qDebug() << "threadIndex: " << threadIndex;
    this->start();
}

VideoPlayer::~VideoPlayer()
{
    clean();
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);
}

/*************************编码器***********************/
int VideoPlayer::initOutput(const char *outFilename) {
    // 初始化输出上下文
    avformat_alloc_output_context2(&outFormatCtx, nullptr, nullptr, outFilename);
    if (!outFormatCtx) {
        qDebug() << "Could not create output context";
        return -1;
    }

    // 查找编码器
    outCodec = avcodec_find_encoder(AV_CODEC_ID_H264);
    if (!outCodec) {
        qDebug() << "Could not find encoder";
        return -1;
    }

    // 创建编码器上下文
    outCodecCtx = avcodec_alloc_context3(outCodec);
    if (!outCodecCtx) {
        qDebug() << "Could not allocate video codec context";
        return -1;
    }

    // 设置编码器参数
    outCodecCtx->bit_rate = 400000;
    outCodecCtx->width = pCodecCtx->width;
    outCodecCtx->height = pCodecCtx->height;
    outCodecCtx->time_base = (AVRational){1, 25}; // 帧率
    outCodecCtx->framerate = (AVRational){25, 1}; // 帧率
    outCodecCtx->gop_size = 10;
    outCodecCtx->max_b_frames = 1;
    outCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P;

    // 打开编码器
    if (avcodec_open2(outCodecCtx, outCodec, nullptr) < 0) {
        qDebug() << "Could not open codec";
        return -1;
    }

    // 创建视频流
    outStream = avformat_new_stream(outFormatCtx, outCodec);
    if (!outStream) {
        qDebug() << "Failed allocating output stream";
        return -1;
    }

    // 设置视频流参数
    avcodec_parameters_from_context(outStream->codecpar, outCodecCtx);

    // 打开输出文件
    if (!(outFormatCtx->oformat->flags & AVFMT_NOFILE)) {
        if (avio_open(&outFormatCtx->pb, outFilename, AVIO_FLAG_WRITE) < 0) {
            qDebug() << "Could not open output file";
            return -1;
        }
    }

    // 写入文件头
    if (avformat_write_header(outFormatCtx, nullptr) < 0) {
        qDebug() << "Error occurred when opening output file";
        return -1;
    }

    return 0;
}

int VideoPlayer::encodeFrame(AVFrame *frame) 
{
    int ret;

    if (!frame) {
        // 如果 frame 为 nullptr，则表示发送结束标志
        ret = avcodec_send_frame(outCodecCtx, nullptr);
        if (ret < 0) {
            qDebug() << "Error sending a frame for encoding";
            return ret;
        }
        return 0;
    }

    // 确保 AVFrame 的属性已正确设置
    if (!frame->format || !frame->width || !frame->height) {
        qDebug() << "Invalid frame: format, width, or height not set.";
        return -1;
    }


    // 发送帧到编码器
    ret = avcodec_send_frame(outCodecCtx, frame);
    if (ret < 0) {
        qDebug() << "Error sending a frame for encoding";
        return ret;
    }

    while (ret >= 0) {
        ret = avcodec_receive_packet(outCodecCtx, &outPacket);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
            break;
        } else if (ret < 0) {
            qDebug() << "Error during encoding";
            return ret;
        }

        // 设置PTS
        outPacket.pts = av_rescale_q_rnd(outPacket.pts, outCodecCtx->time_base, outStream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
        outPacket.dts = av_rescale_q_rnd(outPacket.dts, outCodecCtx->time_base, outStream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
        outPacket.duration = av_rescale_q(outPacket.duration, outCodecCtx->time_base, outStream->time_base);
        outPacket.pos = -1;

        // 写入帧到输出文件
        ret = av_interleaved_write_frame(outFormatCtx, &outPacket);
        if (ret < 0) {
            qDebug() << "Error muxing packet";
            break;
        }

        av_packet_unref(&outPacket);
    }
    return 0;
}

void VideoPlayer::finishOutput() {

    // 写入文件尾
    av_write_trailer(outFormatCtx);

    // 关闭输出文件
    if (!(outFormatCtx->oformat->flags & AVFMT_NOFILE)) {
        avio_closep(&outFormatCtx->pb);
    }

    // 释放编码器上下文
    avcodec_free_context(&outCodecCtx);

    // 释放输出上下文
    avformat_free_context(outFormatCtx);
}


void VideoPlayer::on_addViewNum_slot(int index)
{
    qDebug() << "on_addViewNum_slot";
    threadIndex = index;
}

void VideoPlayer::on_pauseSignal_slot()
{
    qDebug() << "on_pauseSignal_slot";
    m_pause_flag = true;
}

void VideoPlayer::on_playSignal_slot()
{
    qDebug() << "on_playSignal_slot";
    m_pause_flag = false;
}
void VideoPlayer::on_recording_slot(int flag)
{
    qDebug() << "on_recording_slot";
    if(flag)
        m_record_flag = true;
    else
        m_record_flag = false;
}

void VideoPlayer::run()
{
    qDebug() << "run";
    AVPacket packet;               // 封装包
    while(1)
    {
        if(m_pause_flag)
            continue;
        // 读取一帧视频
        if (av_read_frame(pFormatCtx, &packet) < 0) {
            qDebug() << "packet read ending.\n";    // 读完了
            break;
        }

        // 判断是否是视频流
        if (packet.stream_index == videoStream)
        {
            // 解码视频帧
            decode(packet);
            // 释放数据包
            av_packet_unref(&packet);
            // 编码帧
            // encodeFrame(pFrameRGB);
        }
    }
    // 编码剩余帧
    // encodeFrame(nullptr);
    qDebug() << "Ending Decoding Video ..............\n";
    finishOutput();
    clean();
}

int VideoPlayer::videoPlayer_init()
{
    videoStream = -1;

    // 1. 初始化FFMPEG
    av_register_all();
    avformat_network_init();

    // 2. 分配一个AVFormatContext
    pFormatCtx = avformat_alloc_context();

    // 3. 打开视频文件
    if(avformat_open_input(&pFormatCtx, rtspUrl.toUtf8().constData(), NULL, NULL) != 0){
        qDebug() << "can't open the file.\n";
        return -1;
    }
    qDebug() << "open success................\n";
    // 检索信流信息
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        qDebug() << "Could't find stream infomation.\n";
        return -1;
    }
    qDebug() << "Find Stream Information Success ..............\n";


    //  4. 查找文件视频流
    //循环查找视频中包含的流信息，直到找到视频类型的流
    //便将其记录下来 保存到videoStream变量中
    //这里我们现在只处理视频流  音频流先不管他
    for (int i = 0; i < pFormatCtx->nb_streams; i++)
    {
        // if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStream = i;
            break;
        }
    }
    // 如果videoStream为-1 说明没有找到视频流
    if (videoStream == -1) {
        qDebug() << "Didn't find a video stream.\n";
        return -1;
    }
    qDebug() << "Find The Video Stream Information Success ..............\n";

    // 5. 解码器解码
    stream = pFormatCtx->streams[videoStream];          // 获取视频流
    pCodecCtx = stream->codec;                          // 获取解码器上下文
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id); // 查找解码器
    if (pCodec == NULL) {
        qDebug() << "Codec not found.\n";
        return -1;
    }
    qDebug() << "Find The Codec Information Success ..............\n";

    // 打开解码器
    if  (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
        qDebug() << "Could not open codec.\n";
        return -1 ;
    }
    qDebug() << "Open Codec Success ..............\n";

    
    // 初始化数据帧
    pFrame = av_frame_alloc();      // 分配一个AVFrame
    if(pFrame == NULL) {
        qDebug() << "Could not allocate video frame.\n";
        return -1;
    }
    pFrameRGB = av_frame_alloc();   // 分配一个AVFrame
    if(pFrameRGB == NULL) {
        qDebug() << "Could not allocate video pFrameRGB.\n";
        return -1;
    }

    // 确定保存图片的格式
    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height, 1);
    uint8_t *buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));
    av_image_fill_arrays(pFrameRGB->data, pFrameRGB->linesize, buffer, AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height, 1);
    // 转换格式  deprecated pixel format used, make sure you did set range correctly
    img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
                               pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_RGB24, SWS_BILINEAR,
                               NULL, NULL, NULL);
    qDebug() << "Start Decoding Video ..............\n";

    return 0;
}

void VideoPlayer::decode(const AVPacket &packet)
{
    int ret = avcodec_send_packet(pCodecCtx, &packet);
    if(ret < 0) {
        qDebug() << "Error sending a packet for decoding";
        return;
    }

    while (ret >= 0)
    {
        ret = avcodec_receive_frame(pCodecCtx, pFrame);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
            break;
        } else if (ret < 0) {
            qDebug() << "Error during decoding";
            return;
        }

        // 转换为 RGB 格式
        sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize);
        
        // 确保 AVFrame 的属性已正确设置
        pFrameRGB->format = AV_PIX_FMT_RGB24;
        pFrameRGB->width = pCodecCtx->width;
        pFrameRGB->height = pCodecCtx->height;
        
        
        // 将 RGB 数据转换为 QImage
        QImage image(pFrameRGB->data[0], pCodecCtx->width, pCodecCtx->height, pFrameRGB->linesize[0], QImage::Format_RGB888);
        emit sendImage(threadIndex, image);

        // 编码帧
        encodeFrame(pFrameRGB);
    }
}
int VideoPlayer::initEncoderContext()
{
    //查找编码器
    if(nullptr == (outCodec = avcodec_find_encoder(AV_CODEC_ID_H264))) {
        emit errorOccurred(tr("connot find AVCodec."));
        return -1;
    }

    //根据编码器参数设置编码器内容
    if(nullptr == (outCodecCtx = avcodec_alloc_context3(outCodec))) {
        emit errorOccurred(tr("onnot create CodecContext."));
        return -1;
    }

    outCodecCtx->gop_size = 10;             // 10 帧一个I帧
    outCodecCtx->has_b_frames = 0;          // 关闭B帧
    outCodecCtx->max_b_frames = 0;          // 关闭B帧
    outCodecCtx->codec_id = outCodec->id;
    outCodecCtx->time_base.num = pFormatCtx->streams[0]->codec->time_base.num;
    outCodecCtx->time_base.den = pFormatCtx->streams[0]->codec->time_base.den;
    outCodecCtx->pix_fmt = *outCodec->pix_fmts;
    outCodecCtx->width  = pCodecCtx->width;
    outCodecCtx->height = pCodecCtx->height;

    outCodecCtx->me_subpel_quality = 0;
    outCodecCtx->refs = 1;
    outCodecCtx->scenechange_threshold = 0;
    outCodecCtx->trellis = 0;
    outCodecCtx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;

    if(avcodec_open2(outCodecCtx, outCodec, nullptr) < 0)
    {
        emit errorOccurred(tr("open outCodec failed."));
        qDebug() << "open encoder failed." << endl;
        return -1;
    }
    return 0;
}
void VideoPlayer::clean()
{
     if (img_convert_ctx) {
        sws_freeContext(img_convert_ctx);
        img_convert_ctx = nullptr;
    }
    if (pFrameRGB) {
        av_frame_free(&pFrameRGB);
        pFrameRGB = nullptr;
    }
    if (pFrame) {
        av_frame_free(&pFrame);
        pFrame = nullptr;
    }
    if (pCodecCtx) {
        avcodec_free_context(&pCodecCtx);
        pCodecCtx = nullptr;
    }
    if (pFormatCtx) {
        avformat_close_input(&pFormatCtx);
        pFormatCtx = nullptr;
    }
}
