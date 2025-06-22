#ifndef VIDEOENCODER_H
#define VIDEOENCODER_H

#include <QObject>
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

class VideoEncoder : public QObject
{
    Q_OBJECT
public:
    explicit VideoEncoder(QObject *parent = nullptr);
    ~VideoEncoder();
    bool open(const QString& filename, int width, int height, int fps = 25);
    bool encodeFrame(AVFrame* frame);
    void close();

signals:

private:
    AVFormatContext* outFormatCtx = nullptr;
    AVCodecContext* outCodecCtx = nullptr;
    AVCodec* outCodec = nullptr;
    AVStream* outStream = nullptr;
    AVPacket outPacket;
};

#endif // VIDEOENCODER_H
