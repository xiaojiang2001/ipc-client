#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "videoplayer.h"
#include <QQueue>
#include <QImage>
#include <QPaintEvent>
#include "videowidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    VideoPlayer *mplayer;
    QQueue<QImage> que;

    QThread *thread1;
    QThread *thread2;
    QThread *thread3;
    QThread *thread4;

//    VideoWidget *video1;
//    VideoWidget *video2;
//    VideoWidget *video3;
//    VideoWidget *video4;

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void slotGetOneImage(QImage image);
    void thread_func1();
    void thread_func2();
    void thread_func3();
    void thread_func4();
};
#endif // MAINWINDOW_H
