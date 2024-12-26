#include "videowidget.h"
#include <QPainter>

VideoWidget::VideoWidget(QWidget *parent) : QWidget(parent)
{

}

void VideoWidget::addImage(const QImage &image)
{
    que.push_back(image);
    update();  // 请求重绘
}

void VideoWidget::paintEvent(QPaintEvent *event)
{
    if (que.size() <= 0)
        return;
    QImage img = que.front();
    que.pop_front();

    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, width(), height());  // 先画成黑色

    if (img.size().width() <= 0)
        return;

    // 将图像按比例缩放成和窗口一样大小
    QImage image = img.scaled(size(), Qt::KeepAspectRatio);
    int x = width() - image.width();
    int y = height() - image.height();
    x /= 2;
    y /= 2;
    painter.drawImage(QPoint(x, y), image);  // 画出图像
}
