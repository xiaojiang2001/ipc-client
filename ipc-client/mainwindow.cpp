#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //this->resize(900,700);
    

    qDebug() << "in MainWindow";
    qDebug() << "sersion: " << av_version_info();
    qDebug() << avcodec_version();

    mplayer = new VideoPlayer();
    connect(mplayer,&VideoPlayer::sendImage, this , &MainWindow::slotGetOneImage);

    thread1 = new QThread;
    thread2 = new QThread;
    thread3 = new QThread;
    thread4 = new QThread;
    connect(thread1, &QThread::started, this, &MainWindow::thread_func1);
    connect(thread2, &QThread::started, this, &MainWindow::thread_func2);
    connect(thread3, &QThread::started, this, &MainWindow::thread_func3);
    connect(thread4, &QThread::started, this, &MainWindow::thread_func4);

    thread1->start();
    thread2->start();
    thread3->start();
    thread4->start();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotGetOneImage(QImage image)
{
    que.push_back(image);
    update();
}

void MainWindow::thread_func1()
{
   qDebug() << "in thread_func1";
}

void MainWindow::thread_func2()
{
    qDebug() << "in thread_func2";
}

void MainWindow::thread_func3()
{
    qDebug() << "in thread_func3";
}

void MainWindow::thread_func4()
{
    qDebug() << "in thread_func4";
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    if(que.size() <= 0)
        return;
    QImage img = que.front();
    que.pop_front();
    QPainter painter(this);
    painter.setBrush(Qt::black);


    // 获取 ui->widget1 的几何信息
    QRect widgetRect = ui->widget1->geometry();
    painter.drawRect(widgetRect);  //先画成黑色

    if (img.size().width() <= 0)  return;

    // 将图像按比例缩放成和widget1一样大小
    QImage image = img.scaled(widgetRect.size());
    // 计算图像在 widget1 中的绘制位置
    int x = widgetRect.x() + (widgetRect.width() - image.width()) / 2;
    int y = widgetRect.y() + (widgetRect.height() - image.height()) / 2;
    // 在 ui->widget1 上绘制图像
    painter.drawImage(QPoint(x, y), image);
}
