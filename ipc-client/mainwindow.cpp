#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPainter>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // this->resize(900,700);
    camcaeWay = 1;
    ui->radioBtn1->setChecked(true);


    qDebug() << "in MainWindow";
    qDebug() << "sersion: " << av_version_info();
    qDebug() << avcodec_version();

    mplayer = new VideoPlayer();
    connect(mplayer,&VideoPlayer::sendImage, this , &MainWindow::slotGetOneImage);

    thread1 = new QThread;
    connect(thread1, &QThread::started, this, &MainWindow::thread_func1);
    thread1->start();

    connect(ui->radioBtn1, &QRadioButton::clicked, this , [=](){
        camcaeWay = 1;
        widgetView1->show();
        widgetView4->hide();
        widgetView9->hide();
        widgetView16->hide();
    });
    connect(ui->radioBtn4, &QRadioButton::clicked, this , [=](){
        camcaeWay = 4;
        widgetView1->hide();
        widgetView4->show();
        widgetView9->hide();
        widgetView16->hide();
    });
    connect(ui->radioBtn9, &QRadioButton::clicked, this , [=](){
        camcaeWay = 9;
        widgetView1->hide();
        widgetView4->hide();
        widgetView9->show();
        widgetView16->hide();
    });
    connect(ui->radioBtn16, &QRadioButton::clicked, this , [=](){
        camcaeWay = 16;
        widgetView1->hide();
        widgetView4->hide();
        widgetView9->hide();
        widgetView16->show();
    });

    QHBoxLayout* layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    ui->widgetView->setLayout(layout);
    ui->widgetView->setStyleSheet("border: 2px solid blue;");

    // 创建一个widgetView1
    widgetView1 = new QWidget();
    widgetView1->setGeometry(ui->widgetTop->height(), 0, ui->widgetView->width(), ui->widgetView->height());
    // widgetView1->setStyleSheet("background-color: rgb(0, 200, 0);");
    // 并把创建的widgetView1放到widgetMiddle中去
    ui->widgetView->layout()->addWidget(widgetView1);
    widgetView1->show();


    // 创建一个widgetView4 内部表格布局4个widget
    widgetView4 = new QWidget();
    widgetView4->setGeometry(ui->widgetTop->height(), 0, ui->widgetView->width(), ui->widgetView->height());
    // 使用 QGridLayout 替换 QHBoxLayout
    QGridLayout *gridLayout4 = new QGridLayout(widgetView4);
    gridLayout4->setContentsMargins(0, 0, 0, 0); // 设置边距为0
    // 使用 QVector<QWidget*> 存储 widgetView4_1 到 widgetView4_4
    for(int i = 0; i < 4; i++)
    {
        QWidget *widget = new QWidget();
        // widget->setStyleSheet(QString("background-color: rgb(%1, %2, %3);")
        //                       .arg(qrand() % 256)
        //                       .arg(qrand() % 256)
        //                       .arg(qrand() % 256));
        widgetView4Array.append(widget);
        // 将控件添加到 QGridLayout 中
        gridLayout4->addWidget(widget, i / 2, i % 2);
    }
    ui->widgetView->layout()->addWidget(widgetView4);
    widgetView4->hide();



    // 创建一个widgetView9 内部表格布局9个widget
    widgetView9 = new QWidget();
    widgetView9->setGeometry(ui->widgetTop->height(), 0, ui->widgetView->width(), ui->widgetView->height());
    QGridLayout *gridLayout9 = new QGridLayout(widgetView9);
    gridLayout9->setContentsMargins(0, 0, 0, 0); // 设置边距为0
    // 使用 QVector<QWidget*> 存储 widgetView9_1 到 widgetView9_9
    for(int i = 0; i < 9; i++)
    {
        QWidget *widget = new QWidget();
        // widget->setStyleSheet(QString("background-color: rgb(%1, %2, %3);")
        //                       .arg(qrand() % 256)
        //                       .arg(qrand() % 256)
        //                       .arg(qrand() % 256));
        widgetView9Array.append(widget);
        // 将控件添加到 QGridLayout 中
        gridLayout9->addWidget(widget, i / 3, i % 3);
    }
    ui->widgetView->layout()->addWidget(widgetView9);
    widgetView9->hide();


    // 创建一个widgetView16 内部表格布局16个widget
    widgetView16 = new QWidget();
    widgetView16->setGeometry(ui->widgetTop->height(), 0, ui->widgetView->width(), ui->widgetView->height());
    // 使用 QGridLayout 替换 QHBoxLayout
    QGridLayout *gridLayout16 = new QGridLayout(widgetView16);
    gridLayout16->setContentsMargins(0, 0, 0, 0); // 设置边距为0
    // 使用 QVector<QWidget*> 存储 widgetView16_1 到 widgetView16_16
    for(int i = 0; i < 16; i++)
    {
        QWidget *widget = new QWidget();
        // widget->setStyleSheet(QString("background-color: rgb(%1, %2, %3);")
        //                       .arg(qrand() % 256)
        //                       .arg(qrand() % 256)
        //                       .arg(qrand() % 256));
        widgetView16Array.append(widget);
        // 将控件添加到 QGridLayout 中
        gridLayout16->addWidget(widget, i / 4, i % 4);
    }
    ui->widgetView->layout()->addWidget(widgetView16);
    widgetView16->hide();

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

void MainWindow::paintEvent(QPaintEvent *event)
{
    if(que.size() <= 0)
        return;
    QImage img = que.dequeue();
    if (img.size().width() <= 0)  return;


    QPainter painter(this);
    painter.setBrush(Qt::black);

    if(camcaeWay == 1)
    {
        QRect topRect = ui->widgetTop->geometry();          // 获取 widgetTop 的几何信息
        QRect viewRect = ui->widgetView->geometry();           // 获取 widgetView 的几何信息
        int offsetY = topRect.height();                     // 计算 widgetView 相对于 widgetMiddle 的偏移位置 垂直偏移量
        int x = viewRect.x();
        int y = viewRect.y() + offsetY;                     // 计算 widgetView 在 widgetMiddle 中的实际绘制位置
        QImage image = img.scaled(viewRect.size());        // 将图像按比例缩放成和widget1一样大小
        painter.drawImage(x + 9, y + 9, image);                    // 在 ui->widget1 上绘制图像
    }
    else if(camcaeWay == 4)
    {
        QRect topRect  = ui->widgetTop->geometry();          // 获取 widgetTop 的几何信息
        QRect viewRect = ui->widgetView->geometry();           // 获取 widgetView 的几何信息
        int x, y;
        // i / 2  第几排
        // i % 2  第几列
        for(int i = 0; i < 4; i++)
        {
            QRect viewRect = widgetView4Array[i]->geometry();
            x = viewRect.width() * (i % 2) + 6 * (i % 2) + 9;
            y = viewRect.height() * (i / 2) + topRect.height() + 6 * (i / 2) + 9;
            QImage image = img.scaled(viewRect.size());
            painter.drawImage(x, y, image);
        }
    }
    else if(camcaeWay == 9)
    {
        QRect topRect = ui->widgetTop->geometry();          // 获取 widgetTop 的几何信息
        QRect viewRect =  ui->widgetView->geometry();           // 获取 widgetView 的几何信息
        int x, y;
        // i / 3  第几排
        // i % 3  第几列
        for(int i = 0; i < 9; i++)
        {
            QRect viewRect = widgetView9Array[i]->geometry();
            x = viewRect.width() * (i % 3) + 6 * (i % 3) + 9;
            y = viewRect.height() * (i / 3) + topRect.height() + 6 * (i / 3) + 9;
            QImage image = img.scaled(viewRect.size());
            painter.drawImage(x, y, image);
        }
    }
    else if(camcaeWay == 16)
    {
        QRect topRect = ui->widgetTop->geometry();              // 获取 widgetTop 的几何信息
        QRect viewRect =  ui->widgetView->geometry();           // 获取 widgetView 的几何信息
        int x, y;
        // i / 4 第几排
        // i % 4  第几列
        for(int i = 0; i < 16; i++)
        {
            QRect viewRect = widgetView16Array[i]->geometry();
            x = viewRect.width() * (i % 4) + 6 * (i % 4) + 9;
            y = viewRect.height() * (i / 4) + topRect.height() + 6 * (i / 4) + 9;
            QImage image = img.scaled(viewRect.size());
            painter.drawImage(x, y, image);
        }
    }
}
