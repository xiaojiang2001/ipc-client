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


void VideoWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(100, 180, 255)); // 填充背景色
    painter.setPen(Qt::black);
    painter.drawText(rect(), Qt::AlignCenter, m_displayText); // 显示内容
}

void VideoWidget::setDisplayText(const QString& text)
{
    m_displayText = text;
    update();
}
