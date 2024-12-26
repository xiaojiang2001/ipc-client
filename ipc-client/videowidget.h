#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include <QQueue>

class VideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = nullptr);
    void addImage(const QImage &image);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QQueue<QImage> que;

signals:

};

#endif // VIDEOWIDGET_H
