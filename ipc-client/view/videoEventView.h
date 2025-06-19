#ifndef VIDEOEVENTVIEW_H
#define VIDEOEVENTVIEW_H

#include <QWidget>
#include <QPushButton>  

// 定义枚举类型
enum VideoEventType {
    VIDEO_PAUSE,
    VIDEO_PLAY,
    VIDEO_PHOTO
};

class VideoEventView : public QWidget
{
    Q_OBJECT
public:
    explicit VideoEventView(QWidget *parent = nullptr);
    ~VideoEventView();

private:
    QPushButton *pauseBtn;
    QPushButton *playBtn;
    QPushButton *photoBtn;

    void initUI();
    void initConnections();

signals:
    // 统一的 视频事件 控制信号
    void VideoEventOperationRequested(VideoEventType operation);
};

#endif // VIDEOEVENTVIEW_H
