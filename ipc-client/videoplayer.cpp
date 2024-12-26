#include "videoplayer.h"
#include <QDebug>
#include <QImage>
#include <QPixmap>

static struct SwsContext *img_convert_ctx = nullptr;    // 转换格式上下文
VideoPlayer::VideoPlayer()
{
    qDebug() << "version: " << av_version_info();
    qDebug() <<  avcodec_version();
    int ret = videoPlayer_init();
    if(ret < 0) {
        qDebug() << "videoPlayer_init error";
        return;
    }
    start();
}


VideoPlayer::~VideoPlayer()
{
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);
}

void VideoPlayer::run()
{
    qDebug() << "run";
    int ret = 0;
    AVPacket packet;               // 封装包
    while (1)
    {
        // 读取一帧视频
        if (av_read_frame(pFormatCtx, &packet) < 0) {
            qDebug() << "packet read ending.\n";    // 读完了
            break;;
        }

        // 判断是否是视频流
        if (packet.stream_index == videoStream)
        {
            // 解码视频帧
            decode(packet);
            // 释放数据包
            av_packet_unref(&packet);
        }
    }
    qDebug() << "Ending Decoding Video ..............\n";
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
            continue;
        }

        // 转换为 RGB 格式
        sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize);
        // 将 RGB 数据转换为 QImage
        QImage image(pFrameRGB->data[0], pCodecCtx->width, pCodecCtx->height, pFrameRGB->linesize[0], QImage::Format_RGB888);
        emit sendImage(image);
    }
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
