#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H
// ffmpeg 头文件
extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/pixfmt.h>
#include <libavdevice/avdevice.h>
#include <libavutil/imgutils.h>
#include <libswresample/swresample.h>
}

#include <QThread>
#include <QPixmap>

class VideoPlayer : public QThread
{
    Q_OBJECT    //宏，使程序可以使用信号与槽机制；
public:
    VideoPlayer();
    ~VideoPlayer();

    void on_recording_slot(int flag);

protected:
    void run();

private:
    bool m_record_flag;
    bool m_pause_flag;
    int videoPlayer_init();
    int threadIndex;
    void decode(const AVPacket &packet);
    int initEncoderContext();
    void clean();


    AVFormatContext *pFormatCtx;    // 上下文
    AVStream *stream;               // 视频流   由于AVFormatContext释放自动
    AVCodecContext *pCodecCtx;      // 解码器上下文
    AVCodec *pCodec;                // 解码器
    AVFrame *pFrame;                // YUV420帧
    AVFrame *pFrameRGB;             // RGB帧
    int videoStream;                // 视频流索引
    SwsContext *img_convert_ctx ;   // 视频帧转换器

    // QString rtspUrl = "rtsp://rtspstream:c55e63cf6d099c8a00cc7e12daed7a05@zephyr.rtsp.stream/movie";
    // QString rtspUrl = "rtsp://admin:admin123@192.168.1.63:554/mainstream";
    QString rtspUrl = "rtsp://172.32.0.93/live/0";

    // 编码
    AVFormatContext *outFormatCtx;  // 编码器上下文
    AVCodecContext *outCodecCtx;    // 编码器上下文
    AVStream *outStream;            // 编码器流
    AVPacket outPacket;             // 编码器包
    AVCodec *outCodec;              // 编码器
    int initOutput(const char *outFilename);
    int encodeFrame(AVFrame *frame);
    void finishOutput();
    

signals:
    void errorOccurred(const QString &errorMessage);
    void sendImage(int idx, QImage image);  //没获取到一帧图像 就发送此信号

public slots:
    void on_addViewNum_slot(int index);
    void on_pauseSignal_slot();
    void on_playSignal_slot();
};

#endif // VIDEOPLAYER_H
