#ifndef VIDEOEVENTCONTROLLER_H
#define VIDEOEVENTCONTROLLER_H

#include <QObject>
#include <QThread>
#include "videoDecoder.h"
#include "videoEncoder.h"

class VideoEventController : public QThread
{
    Q_OBJECT
public:
    explicit VideoEventController(QObject *parent = nullptr);
    ~VideoEventController();
    void setUrl(const QString& url);
    void startPlay();
    void stopPlay();
    void startRecord(const QString& filename);
    void stopRecord();

signals:
    void sendImage(int idx, const QImage& image);

protected:
    void run();

private:
    VideoDecoder* decoder = nullptr;
    VideoEncoder* encoder = nullptr;
    AVFrame* frame = nullptr;
    QString url;
    bool m_pause_flag = false;
    bool m_record_flag = false;
    int threadIndex;
};

#endif // VIDEOEVENTCONTROLLER_H
