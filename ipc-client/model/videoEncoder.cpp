#include "videoEncoder.h"
#include <QDebug>

VideoEncoder::VideoEncoder(QObject *parent) : QObject(parent)
{
    outFormatCtx = nullptr;
    outCodecCtx = nullptr;
    outCodec = nullptr;
    outStream = nullptr;
}

VideoEncoder::~VideoEncoder()
{
    close();
}

bool VideoEncoder::open(const QString& filename, int width, int height, int fps)
{
    avformat_alloc_output_context2(&outFormatCtx, nullptr, nullptr, filename.toUtf8().constData());
    if (!outFormatCtx) {
        qDebug() << "Could not create output context";
        return false;
    }
    outCodec = avcodec_find_encoder(AV_CODEC_ID_H264);
    if (!outCodec) {
        qDebug() << "Could not find encoder";
        return false;
    }
    outCodecCtx = avcodec_alloc_context3(outCodec);
    if (!outCodecCtx) {
        qDebug() << "Could not allocate video codec context";
        return false;
    }
    outCodecCtx->bit_rate = 400000;
    outCodecCtx->width = width;
    outCodecCtx->height = height;
    outCodecCtx->time_base = (AVRational){1, fps};
    outCodecCtx->framerate = (AVRational){fps, 1};
    outCodecCtx->gop_size = 10;
    outCodecCtx->max_b_frames = 1;
    outCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P;

    if (avcodec_open2(outCodecCtx, outCodec, nullptr) < 0) {
        qDebug() << "Could not open codec";
        return false;
    }
    outStream = avformat_new_stream(outFormatCtx, outCodec);
    if (!outStream) {
        qDebug() << "Failed allocating output stream";
        return false;
    }
    avcodec_parameters_from_context(outStream->codecpar, outCodecCtx);

    if (!(outFormatCtx->oformat->flags & AVFMT_NOFILE)) {
        if (avio_open(&outFormatCtx->pb, filename.toUtf8().constData(), AVIO_FLAG_WRITE) < 0) {
            qDebug() << "Could not open output file";
            return false;
        }
    }
    if (avformat_write_header(outFormatCtx, nullptr) < 0) {
        qDebug() << "Error occurred when opening output file";
        return false;
    }
    return true;
}



bool VideoEncoder::encodeFrame(AVFrame* frame)
{
    int ret;
    if (!frame) {
        ret = avcodec_send_frame(outCodecCtx, nullptr);
        if (ret < 0) {
            qDebug() << "Error sending a frame for encoding";
            return false;
        }
        return true;
    }
    if (!frame->format || !frame->width || !frame->height) {
        qDebug() << "Invalid frame: format, width, or height not set.";
        return false;
    }
    ret = avcodec_send_frame(outCodecCtx, frame);
    if (ret < 0) {
        qDebug() << "Error sending a frame for encoding";
        return false;
    }
    while (ret >= 0) {
        ret = avcodec_receive_packet(outCodecCtx, &outPacket);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) break;
        else if (ret < 0) {
            qDebug() << "Error during encoding";
            return false;
        }
        outPacket.pts = av_rescale_q_rnd(outPacket.pts, outCodecCtx->time_base, outStream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
        outPacket.dts = av_rescale_q_rnd(outPacket.dts, outCodecCtx->time_base, outStream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
        outPacket.duration = av_rescale_q(outPacket.duration, outCodecCtx->time_base, outStream->time_base);
        outPacket.pos = -1;
        ret = av_interleaved_write_frame(outFormatCtx, &outPacket);
        if (ret < 0) {
            qDebug() << "Error muxing packet";
            break;
        }
        av_packet_unref(&outPacket);
    }
    return true;
}

void VideoEncoder::close()
{
    if (outFormatCtx) {
        av_write_trailer(outFormatCtx);
        if (!(outFormatCtx->oformat->flags & AVFMT_NOFILE)) {
            avio_closep(&outFormatCtx->pb);
        }
        avcodec_free_context(&outCodecCtx);
        avformat_free_context(outFormatCtx);
        outFormatCtx = nullptr;
        outCodecCtx = nullptr;
        outCodec = nullptr;
        outStream = nullptr;
    }
}