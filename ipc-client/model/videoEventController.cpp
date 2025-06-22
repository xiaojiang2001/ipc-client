#include "videoEventController.h"
#include <QDebug>

VideoEventController::VideoEventController(QObject *parent) : QThread(parent)
{
    decoder = new VideoDecoder(this);
    encoder = nullptr;
    m_pause_flag = false;
    m_record_flag = false;
    threadIndex = 0;
    frame = nullptr;

    url = "rtsp://192.168.1.153/live/0";
    m_pause_flag = false;
    this->start();
}


VideoEventController::~VideoEventController()
{
    stopPlay();
    if (encoder) 
        delete encoder;
}

void VideoEventController::setUrl(const QString& url)
{
    this->url = url;
}

void VideoEventController::startPlay()
{
    m_pause_flag = false;
    if (!isRunning()) this->start();
}

void VideoEventController::stopPlay()
{
    m_pause_flag = true;
    wait();
    decoder->close();
    if (encoder) encoder->close();
}

void VideoEventController::startRecord(const QString& filename)
{
    if (!encoder) encoder = new VideoEncoder(this);
    // 假设解码器已打开
    // encoder->open(filename, decoder->getWidth(), decoder->getHeight());
    m_record_flag = true;
}

void VideoEventController::stopRecord()
{
    m_record_flag = false;
    if (encoder) encoder->close();
}

void VideoEventController::run()
{
    if (!decoder->openUrl(url)) {
        qDebug() << "open video failed";
        return;
    }

    if (!decoder->initDecoder(&frame)) {
        qDebug() << "initDecoder failed";
        return;
    }

    QImage image;
    while (!m_pause_flag) 
    {
        if (decoder->readFrame(image, &frame)) 
        {
            emit sendImage(threadIndex, image);
            // // 录制
            // if (m_record_flag && encoder && frame) {
            //     encoder->encodeFrame(frame);
            // }
        } else {
            qDebug() << "read frame failed";
            break;
        }
    }
    decoder->close();
    if (encoder) encoder->close();
}
