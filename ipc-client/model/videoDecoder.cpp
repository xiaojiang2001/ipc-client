#include "videoDecoder.h"
#include <QDebug>
#include <QImage>

VideoDecoder::VideoDecoder(QObject *parent) : QObject(parent)
{
    pFormatCtx = nullptr;
    pCodecCtx = nullptr;
    stream = nullptr;
    pCodec = nullptr;
    pFrame = nullptr;
    pFrameRGB = nullptr;
    img_convert_ctx = nullptr;
    videoStream = -1;
}

VideoDecoder::~VideoDecoder()
{
    close();
}

bool VideoDecoder::openUrl(const QString& url)
{
    videoStream = -1;
    // 1. 初始化FFMPEG
    av_register_all();
    // 2. 分配一个AVFormatContext
    avformat_network_init();

    pFormatCtx = avformat_alloc_context();
    
    // 3. 打开视频文件
    if(avformat_open_input(&pFormatCtx, url.toUtf8().constData(), NULL, NULL) != 0){
        qDebug() << "can't open the file.";
        return false;
    }
    qDebug() << "open success................\n";
    // 检索信流信息
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        qDebug() << "Could't find stream infomation.";
        return false;
    }
    qDebug() << "Find Stream Information Success ..............\n";

    //  4. 查找文件视频流
    //循环查找视频中包含的流信息，直到找到视频类型的流
    //便将其记录下来 保存到videoStream变量中
    //这里我们现在只处理视频流  音频流先不管他
    for (int i = 0; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStream = i;
            break;
        }
    }
    // 如果videoStream为-1 说明没有找到视频流
    if (videoStream == -1) {
        qDebug() << "Didn't find a video stream.";
        return false;
    }
    qDebug() << "Find The Video Stream Information Success ..............\n";

    return true;
}

bool VideoDecoder::initDecoder(AVFrame** frame)
{
    // 1. 解码器解码
    stream = pFormatCtx->streams[videoStream];              // 获取视频流
    pCodecCtx = stream->codec;                              // 获取解码器上下文
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);     // 查找解码器
    if (pCodec == NULL) {
        qDebug() << "Codec not found.";
        return false;
    }
    qDebug() << "Find The Codec Information Success ..............\n";

     // 2. 打开解码器
    if  (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
        qDebug() << "Could not open codec.";
        return false;
    }
    qDebug() << "Open Codec Success ..............\n";

    // 3. 初始化数据帧
    *frame = av_frame_alloc();      // 分配一个AVFrame
    if(*frame == NULL) {
        qDebug() << "Could not allocate video frame.\n";
        return false;
    }
    pFrameRGB = av_frame_alloc();   // 分配一个AVFrame
    if(pFrameRGB == NULL) {
        qDebug() << "Could not allocate video pFrameRGB.\n";
        return false;
    }

    // 4. 确定保存图片的格式
    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height, 1);
    uint8_t *buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));
    av_image_fill_arrays(pFrameRGB->data, pFrameRGB->linesize, buffer, AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height, 1);
     // 转换格式  deprecated pixel format used, make sure you did set range correctly
    img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
                                     pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_RGB24, SWS_BILINEAR,
                                     NULL, NULL, NULL);
    qDebug() << "Start Decoding Video ..............\n";
    return true;
}


bool VideoDecoder::readFrame(QImage& image, AVFrame** frame)
{
    AVPacket packet;    // 封装包
    int ret;
    // 读取一帧视频
    if (av_read_frame(pFormatCtx, &packet) < 0) {
        qDebug() << "packet read ending.\n";    // 读完了
        return false;
    }

    // 判断是否是视频流
    if (packet.stream_index == videoStream)
    {
        // 解码
        ret = avcodec_send_packet(pCodecCtx, &packet);
        if(ret < 0) {
            qDebug() << "Error sending a packet for avcodec_send_packet";
            return false;
        }

        while (ret >= 0)
        {
            ret = avcodec_receive_frame(pCodecCtx, *frame);
            if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                break;
            } else if (ret < 0) {
                qDebug() << "Error during decoding";
                return false;
            }

            // 转换为 RGB 格式
            sws_scale(img_convert_ctx, (const uint8_t* const*)(*frame)->data, (*frame)->linesize, 0, pCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize);
            
            
            // 确保 AVFrame 的属性已正确设置
            pFrameRGB->format = AV_PIX_FMT_RGB24;
            pFrameRGB->width = pCodecCtx->width;
            pFrameRGB->height = pCodecCtx->height;
            
            
            // 将 RGB 数据转换为 QImage
            image = QImage(pFrameRGB->data[0], pCodecCtx->width, pCodecCtx->height, pFrameRGB->linesize[0], QImage::Format_RGB888);


            // if (rawFrame) 
            // *rawFrame = pFrameRGB;
        }
        // 释放数据包
        av_packet_unref(&packet);
    }
    return true;
}


/*
bool VideoDecoder::readFrame(QImage& image, AVFrame** rawFrame)
{
    AVPacket packet;
    int ret = av_read_frame(pFormatCtx, &packet);
    if (ret < 0) {
        qDebug() << "av_read_frame error";
        return false;
    }
    bool gotFrame = false;
    if (packet.stream_index == videoStream) 
    {
        ret = avcodec_send_packet(pCodecCtx, &packet);
        if (ret < 0) {
            qDebug() << "Error sending a packet for decoding";
            av_packet_unref(&packet);
            return false;
        }
        while (ret >= 0) 
        {
            ret = avcodec_receive_frame(pCodecCtx, pFrame);
            if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                qDebug() << "Error during decoding1";
                break;
            }
            else if (ret < 0) {
                qDebug() << "Error during decoding2";
                break;
            }
            
            // 转换为 RGB 格式
            sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize);
            
            // 确保 AVFrame 的属性已正确设置
            pFrameRGB->format = AV_PIX_FMT_RGB24;
            pFrameRGB->width = pCodecCtx->width;
            pFrameRGB->height = pCodecCtx->height;

            // 将 RGB 数据转换为 QImage
            image = QImage(pFrameRGB->data[0], pCodecCtx->width, pCodecCtx->height, pFrameRGB->linesize[0], QImage::Format_RGB888).copy();
            
            // if (rawFrame) 
            //     *rawFrame = pFrameRGB;
            
            gotFrame = true;
            break;
        }

        // 释放数据包
        av_packet_unref(&packet);
    }

    return gotFrame;
}
*/

int VideoDecoder::getWidth() const
{
    return pCodecCtx ? pCodecCtx->width : 0;
}

int VideoDecoder::getHeight() const
{
    return pCodecCtx ? pCodecCtx->height : 0;
}

void VideoDecoder::close()
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
