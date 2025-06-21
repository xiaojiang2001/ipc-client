#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QString>

class VideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = nullptr);

    void setDisplayText(const QString& text);

signals:
    void doubleClicked(VideoWidget*);   // Signal emitted when the widget is double-clicked

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *) override;

private:
    QString m_displayText;
};

#endif // VIDEOWIDGET_H
