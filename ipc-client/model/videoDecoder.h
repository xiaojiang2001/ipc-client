#ifndef VIDEODECODER_H
#define VIDEODECODER_H

#include <QObject>
#include <QImage>
extern "C" {
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
    #include <libavutil/imgutils.h>
}

class VideoDecoder : public QObject
{
    Q_OBJECT
public:
    explicit VideoDecoder(QObject *parent = nullptr);
    ~VideoDecoder();
    bool openUrl(const QString& url);
    bool initDecoder(AVFrame** frame);
    bool readFrame(QImage& image, AVFrame** rawFrame = nullptr);
    void close();

    int getWidth() const;
    int getHeight() const;

signals:

private:
    AVFormatContext* pFormatCtx = nullptr;
    AVCodecContext* pCodecCtx = nullptr;  
    AVStream *stream = nullptr;     
    AVCodec* pCodec = nullptr;
    AVFrame* pFrame = nullptr;
    AVFrame* pFrameRGB = nullptr;
    SwsContext* img_convert_ctx = nullptr;
    int videoStream ;
};

#endif // VIDEODECODER_H
