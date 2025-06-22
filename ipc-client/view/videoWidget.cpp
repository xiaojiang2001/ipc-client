#include "videoWidget.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>

VideoWidget::VideoWidget(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("border: 2px solid red; border-radius: 5px; padding: 5px;");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumSize(40, 40);
    setVisible(true);
}

void VideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit doubleClicked(this);
    QWidget::mouseDoubleClickEvent(event);
}

void VideoWidget::setImage(const QImage& img)
{
    m_image = img;
    update();
}

void VideoWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if (!m_image.isNull()) {
        painter.drawImage(rect(), m_image); // 拉伸填充
    } else {
        painter.fillRect(rect(), QColor(100, 180, 255));
        painter.setPen(Qt::black);
        painter.drawText(rect(), Qt::AlignCenter, m_displayText);
    }
}
