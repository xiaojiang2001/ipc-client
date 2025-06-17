#ifndef VIDEOEVENTVIEW_H
#define VIDEOEVENTVIEW_H

#include <QWidget>
#include <QPushButton>  

class VideoEventView : public QWidget
{
    Q_OBJECT
public:
    explicit VideoEventView(QWidget *parent = nullptr);
private:
    QPushButton *pauseBtn;
    QPushButton *playBtn;
    QPushButton *photoBtn;

signals:

};

#endif // VIDEOEVENTVIEW_H
