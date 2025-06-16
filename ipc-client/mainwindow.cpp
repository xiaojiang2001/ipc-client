#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPainter>
#include <QWidget>
#include <QMenu>
#include <QContextMenuEvent>
#include <QDir>
#include <QMessageBox>
#include <QMessageBox>
#include  <QButtonGroup>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
// , ui(new Ui::MainWindow)
{
    this->resize(1200,800);

    // 创建一个中心部件
    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    // 创建垂直布局
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // 通用的边框样式
    QString borderStyle = "border: 2px solid blue; border-radius: 5px; padding: 5px;";
    // QString borderStyle = "";

    // 创建多个 widget 容器并添加到垂直布局中
    widget1 = new QWidget();
    widget2 = new QWidget();
    widget3 = new QWidget();


    widget1->setStyleSheet(borderStyle);
    // widget2->setStyleSheet(borderStyle);
    // widget3->setStyleSheet(borderStyle);

    mainLayout->addWidget(widget1);
    mainLayout->addWidget(widget2);   
    mainLayout->addWidget(widget3);

    // 一次性设置三个widget的比例为10:25:1
    mainLayout->setStretch(0, 10);
    mainLayout->setStretch(1, 25);
    mainLayout->setStretch(2, 2);
    
    // 设置布局的间距
    mainLayout->setSpacing(10);     // 间隔
    mainLayout->setContentsMargins(10, 10, 10, 10);     //左 上 右 下


    // RadioBtn
    // 为widget1创建水平布局
    QHBoxLayout *radioBtnLayout = new QHBoxLayout(widget3);

    // 创建和添加Label
    QLabel *label = new QLabel("view grid");
    radioBtnLayout->addWidget(label);
    // 创建RadioButton组
    QButtonGroup *buttonGroup = new QButtonGroup(this);
    // 创建4个RadioButton并添加到布局
    for(int i = 1; i <= 4; i++) {
        QRadioButton *radio = new QRadioButton(QString("%1").arg(i*i));
        buttonGroup->addButton(radio);
        radioBtnLayout->addWidget(radio);

        if(i == 1)
            radio->setChecked(true);  // 设置第一个按钮为选中状态
    }

    // 添加弹簧
    radioBtnLayout->addStretch();
    
    // 设置布局的间距
    radioBtnLayout->setSpacing(10);
    mainLayout->addWidget(widget3);



    // 为widget2创建水平布局
    QHBoxLayout *viewLayout = new QHBoxLayout(widget2);
    // 创建两个子widget
    widgetView = new QWidget();
    widgetPTZ = new QWidget();
    widgetView->setStyleSheet(borderStyle);
    
    // 添加到水平布局中，并设置比例为4:1
    viewLayout->addWidget(widgetView, 4);   // 占4份
    viewLayout->addWidget(widgetPTZ, 1);    // 占1份

    // 设置布局的间距
    viewLayout->setSpacing(10);
    viewLayout->setContentsMargins(5, 5, 5, 5);

    // init_data_lable();
    init_ptz_btn();

/*
    ui->setupUi(this);


    this->resize(1200,800);

    camcaeWay = 1;
    ui->radioBtn1->setChecked(true);
   
    // 初始化queArray为16个队列
    queArray.resize(16);
    showViewNum = 1;

    m_pause_flag = false;


    qDebug() << "in MainWindow";
    qDebug() << "sersion: " << av_version_info();
    qDebug() << avcodec_version();

    mplayer = new VideoPlayer();
    connect(mplayer,&VideoPlayer::sendImage, this , &MainWindow::slotGetOneImage);

    connect(ui->radioBtn1, &QRadioButton::clicked, this , &MainWindow::on_radioBtn1_clicked);
    connect(ui->radioBtn4, &QRadioButton::clicked, this , &MainWindow::on_radioBtn2_clicked);
    connect(ui->radioBtn9, &QRadioButton::clicked, this , &MainWindow::on_radioBtn3_clicked);
    connect(ui->radioBtn16, &QRadioButton::clicked, this , &MainWindow::on_radioBtn4_clicked);

    init_gridView();
    init_control_btn();
    init_data_lable();
    
    // 控制按钮
    connect(pauseBtn,   &QPushButton::clicked, this, &MainWindow::on_pauseBtn_clicked);
    connect(playBtn,    &QPushButton::clicked, this, &MainWindow::on_replayBtn_clicked);
    connect(photoBtn,   &QPushButton::clicked, this, &MainWindow::on_photoBtn_clicked);
    connect(startBtn,   &QPushButton::clicked, this, &MainWindow::on_startBtn_clicked);
    connect(stopBtn,    &QPushButton::clicked, this, &MainWindow::on_stopBtn_clicked);
    connect(led1btn,    &QPushButton::clicked, this, &MainWindow::on_led1btn_clicked);
    connect(led2btn,    &QPushButton::clicked, this, &MainWindow::on_led2btn_clicked);
    connect(led3btn,    &QPushButton::clicked, this, &MainWindow::on_led3btn_clicked);
    
    // 向播放器发送信号
    connect(this, &MainWindow::addViewNum,  mplayer,  &VideoPlayer::on_addViewNum_slot);
    connect(this, &MainWindow::pauseSignal, mplayer,  &VideoPlayer::on_pauseSignal_slot);
    connect(this, &MainWindow::playSignal,  mplayer,  &VideoPlayer::on_playSignal_slot);
    connect(this, &MainWindow::recordSignal,  mplayer,  &VideoPlayer::on_recording_slot);
    
    // 接收错误信号
    connect(mplayer, &VideoPlayer::errorOccurred, this, &MainWindow::on_errorOccurred);

    client = new TcpClient();
    // 接收服务器数据
    connect(client, &TcpClient::dataReceived, this, &MainWindow::on_tcpReadyDateHadler);
*/

}
MainWindow::~MainWindow()
{
    delete ui;
    delete mplayer;

    // QVector<QWidget*> widgetView4Array;
    for (auto item : widgetView4Array) {
        delete item;
    }
    for (auto item : widgetView9Array) {
        delete item;
    }
    for (auto item : widgetView16Array) {
        delete item;
    }

    delete widgetView1;
    delete widgetView4;
    delete widgetView9;
    delete widgetView16;

    delete pauseBtn;
    delete playBtn;
    delete photoBtn;

    delete okBtn;         
    delete ptzUpBtn;      
    delete ptzDownBtn;    
    delete ptzLeftBtn;    
    delete ptzRightBtn;
}


// data = temp:27.2 humi:46.0 co2:533 light:22.7\n
void MainWindow::on_tcpReadyDateHadler(const QByteArray &data)
{
    QString rawData = QString(data).trimmed();  // 转换为QString并去除首尾空格
    qDebug() << "Received data:" << rawData;

    // 按空格分割键值对
    QStringList pairs = rawData.split(' ', QString::SkipEmptyParts);

    // 解析每个键值对
    QMap<QString, QString> envData;
    for (const QString &pair : pairs) {
        QStringList keyValue = pair.split(':');
        if (keyValue.size() == 2) {
            envData[keyValue[0]] = keyValue[1];
        }
    }

    // 提取具体值（示例）
    QString temp = envData.value("temp", "N/A");
    QString humi = envData.value("humi", "N/A");
    QString co2 = envData.value("co2", "N/A");
    QString light = envData.value("light", "N/A");

    temp += " °C";
    humi += " %";
    light += " lux";
    co2 += " ppm";

    // 显示到 QTextEdit
    lineEdit_co2->setText(co2);
    lineEdit_tempature->setText(temp);
    lineEdit_humidity->setText(humi);
    lineEdit_light->setText(light); 
    // ui->textEdit->setPlainText(displayText);  // 替换显示
}


void MainWindow::on_errorOccurred(const QString &errorMessage)
{
    QMessageBox::warning(this, tr("Save Video"), errorMessage);
}

// 槽函数实现
void MainWindow::showContextMenu(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);
    QAction *action = contextMenu.addAction(tr("show"));

    // 显示菜单
    QAction *selectedAction = contextMenu.exec(widgetView1->mapToGlobal(pos));

    // 处理选择的动作
    if (selectedAction == action) 
    {
        // 超出每种情况的上届
        if(camcaeWay == 1 || camcaeWay == 4 && showViewNum >= 4 || camcaeWay == 9 && showViewNum >= 9 || camcaeWay == 16 && showViewNum >= 16)
            return;
        qDebug() << "Action  selected";
        showViewNum++;
        // 创建新的播放器 并绑定接收槽函数
        VideoPlayer *mplayer = new VideoPlayer();
        connect(mplayer,&VideoPlayer::sendImage, this , &MainWindow::slotGetOneImage);
        emit addViewNum(showViewNum - 1);
    } 
}

void MainWindow::slotGetOneImage(int idx, QImage image)
{
    queArray[idx].push_back(image);
    tempImage = image;
    update();
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    // if (img.size().width() <= 0)  
    //     return;

    QPainter painter(this);
    painter.setBrush(Qt::black);

    switch (camcaeWay)
    {
        case 1:
        {
            if (queArray[0].size() == 0)
                return;
            QImage img = queArray[0].dequeue();
            if(img.size().width() > 0 && img.size().height() > 0)
                paintImage(painter, widgetView1, img);
        }
        break;
        case 4:
        {
            if(showViewNum >= 4)
                showViewNum = 4;
            QVector<QImage> imgArray(showViewNum);
            // QImage img = queArray[0].dequeue();
            for(int i = 0; i < showViewNum; i++)
            {
                if(queArray[i].size() > 0){
                    imgArray[i] = queArray[i].dequeue();
                    paintImage(painter, widgetView4Array[i], imgArray[i]);
                }
            }
        }
        break;

        case 9:
        {
            if(showViewNum >= 9)
                showViewNum = 9;
            QVector<QImage> imgArray(showViewNum);
            // QImage img = queArray[0].dequeue();
            for(int i = 0; i < showViewNum; i++)
            {
                if(queArray[i].size() > 0){
                    imgArray[i] = queArray[i].dequeue();
                    paintImage(painter, widgetView9Array[i], imgArray[i]);
                }
            }
        }
        break;

        case 16:
        {
           if(showViewNum >= 16)
                showViewNum = 16;
            QVector<QImage> imgArray(showViewNum);
            // QImage img = queArray[0].dequeue();
            for(int i = 0; i < showViewNum; i++)
            {
                if(queArray[i].size() > 0){
                    imgArray[i] = queArray[i].dequeue();
                    paintImage(painter, widgetView16Array[i], imgArray[i]);
                }
            }
        }
        break;

        default:
            qDebug() << "camcaeWay error";
        break;
    }
}

// 在某个特定的窗口上绘制图像
void MainWindow::paintImage(QPainter &painter, QWidget* widget, QImage &img)
{
   if (!widget || img.isNull())
       return;

    // 获取 widget 在当前窗口中的几何信息
    QRect widgetRect = QRect(mapFromGlobal(widget->mapToGlobal(widget->rect().topLeft())), widget->rect().size());
    QImage image = img.scaled(widgetRect.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawImage(widgetRect, image);
}

void MainWindow::init_gridView()
{
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
    // 设置上下文菜单策略
    widgetView1->setContextMenuPolicy(Qt::CustomContextMenu);
    // 连接信号到槽
    connect(widgetView1, &QWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);
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
    // 设置上下文菜单策略
    widgetView4->setContextMenuPolicy(Qt::CustomContextMenu);
    // 连接信号到槽
    connect(widgetView4, &QWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);
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
        widgetView9Array.append(widget);
        // 将控件添加到 QGridLayout 中
        gridLayout9->addWidget(widget, i / 3, i % 3);
    }
    ui->widgetView->layout()->addWidget(widgetView9);
    // 设置上下文菜单策略
    widgetView9->setContextMenuPolicy(Qt::CustomContextMenu);
    // 连接信号到槽
    connect(widgetView9, &QWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);
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
        widgetView16Array.append(widget);
        // 将控件添加到 QGridLayout 中
        gridLayout16->addWidget(widget, i / 4, i % 4);
    }
    ui->widgetView->layout()->addWidget(widgetView16);
        // 设置上下文菜单策略
    widgetView16->setContextMenuPolicy(Qt::CustomContextMenu);
    // 连接信号到槽
    connect(widgetView16, &QWidget::customContextMenuRequested, this, &MainWindow::showContextMenu);
    widgetView16->hide();
}

void MainWindow::init_ptz_btn()
{
    pauseBtn  = new QPushButton("pause",this);
    playBtn = new QPushButton("play", this);
    photoBtn  = new QPushButton("photo",this);
    okBtn  = new QPushButton("ok",this);
    ptzUpBtn = new QPushButton("up",this);
    ptzDownBtn = new QPushButton("down",this);
    ptzLeftBtn = new QPushButton("left",this);
    ptzRightBtn = new QPushButton("right",this);

    //设置最小值、跳转按钮大小
    pauseBtn->setMinimumSize(50,35);
    playBtn->setMinimumSize(50,35);
    photoBtn->setMinimumSize(50,35);
    okBtn->setMinimumSize(50,35);
    ptzUpBtn->setMinimumSize(50,35);  
    ptzDownBtn->setMinimumSize(50,35); 
    ptzLeftBtn->setMinimumSize(50,35);
    ptzRightBtn->setMinimumSize(50,35);


    // 网格布局
    QGridLayout *ptzLayout = new QGridLayout;              
    ptzLayout->setSpacing(5);     //  设置控件之间的间隔
    //网格不同坐标添加不同的组件
    ptzLayout->addWidget(pauseBtn, 0, 0);
    ptzLayout->addWidget(playBtn,  0, 1);
    ptzLayout->addWidget(photoBtn, 1, 0);
    ptzLayout->addWidget(okBtn, 1, 1);
    ptzLayout->addWidget(ptzUpBtn, 2, 0);
    ptzLayout->addWidget(ptzDownBtn, 2, 1);
    ptzLayout->addWidget(ptzLeftBtn, 3, 0);
    ptzLayout->addWidget(ptzRightBtn, 3, 1);

    widgetPTZ->setLayout(ptzLayout);
}




void MainWindow::init_data_lable()
{
    label_tempature = new QLabel("tempature:", this);
    label_humidity  = new QLabel("humidity:", this);
    label_co2       = new QLabel("CO2:", this);
    label_light     = new QLabel("light:", this);
        


    lineEdit_tempature  = new QLineEdit(this);
    lineEdit_humidity   = new QLineEdit(this);
    lineEdit_co2        = new QLineEdit(this);
    lineEdit_light      = new QLineEdit(this);
    lineEdit_tempature->setText("26.0 'C");
    lineEdit_humidity->setText("47.5 %");
    lineEdit_co2->setText("350 ppm");
    lineEdit_light->setText("10.9 lux");


    // 网格布局
    QGridLayout *layout = new QGridLayout;              
    layout->setSpacing(10);     //  设置控件之间的间隔
    //网格不同坐标添加不同的组件
    layout->addWidget(label_tempature,      0, 0);
    layout->addWidget(lineEdit_tempature,   0, 1);
    layout->addWidget(label_humidity,      0, 2);
    layout->addWidget(lineEdit_humidity,    0, 3);

    layout->addWidget(label_co2,      1, 0);
    layout->addWidget(lineEdit_co2,   1, 1);
    layout->addWidget(label_light,      1, 2);
    layout->addWidget(lineEdit_light,    1, 3);

    widget1->setLayout(layout);
}


// 控制按钮槽函数
void MainWindow::on_pauseBtn_clicked()
{
    if(m_pause_flag == true)
        return;
    m_pause_flag = true;
    emit pauseSignal();
}
void MainWindow::on_replayBtn_clicked()
{
    if(m_pause_flag == false)
        return;
    m_pause_flag = false;
    emit playSignal();
}

void MainWindow::on_photoBtn_clicked()
{
    static int i = 0;
    QImage img;
    if(!queArray[0].empty())
        img = queArray[0].front();
    else
        img = tempImage;

    QString name = "image" + QString::number(i++) + ".jpg";
    saveImageToJPEG(img, name);

}

void MainWindow::on_led1btn_clicked()
{
    client->sendData("led1\n");
}

void MainWindow::on_led2btn_clicked()
{
    client->sendData("led2\n");
}

void MainWindow::on_led3btn_clicked()
{
    client->sendData("led3\n");
}



void MainWindow::on_startBtn_clicked()
{
    // emit recordSignal(1);
    client->connectToServer("192.168.1.134", 8888);
}

void MainWindow::on_stopBtn_clicked()
{
    // emit recordSignal(0);
    client->disconnectFromServer();
}


void MainWindow::saveImageToJPEG(QImage image, QString name)
{
    // 获取当前工作目录
    QDir currentDir = QDir::current();
    // 获取上一级目录
    QDir parentDir = currentDir.cdUp() ? currentDir : QDir::root();
    // 输出路径
    QString outputDirPath = parentDir.filePath("output");

    // 检查并创建 output 文件夹
    QDir outputDir(outputDirPath);
    if (!outputDir.exists()) {
        if (!outputDir.mkpath(".")) {
            QMessageBox::warning(this, tr("Save Image"),
                                 tr("Failed to create output directory."));
            return;
        }
    }
    
    // 生成文件的完整路径
    QString fileName = outputDir.filePath(name);

    // 保存图像到文件
    if (!image.save(fileName, "JPEG")) {
        QMessageBox::warning(this, tr("Save Image"),
                             tr("Failed to save image to %1.").arg(fileName));
    } else {
        QMessageBox::information(this, tr("Save Image"),
                                 tr("Image saved successfully to %1.").arg(fileName));
    }
}


void MainWindow::on_radioBtn1_clicked()
{
    camcaeWay = 1;
    showViewNum = 1;
    widgetView1->show();
    widgetView4->hide();
    widgetView9->hide();
    widgetView16->hide();
}
void MainWindow::on_radioBtn2_clicked()
{
    camcaeWay = 4;
    showViewNum = 1;
    widgetView1->hide();
    widgetView4->show();
    widgetView9->hide();
    widgetView16->hide();
}
void MainWindow::on_radioBtn3_clicked()
{
    camcaeWay = 9;
    showViewNum = 1;
    widgetView1->hide();
    widgetView4->hide();
    widgetView9->show();
    widgetView16->hide();
}
void MainWindow::on_radioBtn4_clicked()
{
    camcaeWay = 16;
    showViewNum = 1;
    widgetView1->hide();
    widgetView4->hide();
    widgetView9->hide();
    widgetView16->show();
}
