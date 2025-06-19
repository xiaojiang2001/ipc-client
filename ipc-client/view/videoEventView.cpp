#include "videoEventView.h"
#include <QHBoxLayout>
VideoEventView::VideoEventView(QWidget *parent) : QWidget(parent)
{
    initUI();
    initConnections();
}

VideoEventView::~VideoEventView()
{
    // 析构函数中不需要手动删除按钮，Qt会自动管理子控件的内存
}

void VideoEventView::initUI()
{    pauseBtn  = new QPushButton("pause",this);
    playBtn = new QPushButton("player", this);
    photoBtn  = new QPushButton("photo",this);
    
    //设置最小值、跳转按钮大小
    pauseBtn->setMinimumSize(50,35);
    playBtn->setMinimumSize(50,35);
    photoBtn->setMinimumSize(50,35);

    // 水平布局
    QHBoxLayout *videoEventLayout = new QHBoxLayout(this);
    videoEventLayout->setSpacing(5);     // 设置控件之间的间隔
    // 水平布局中添加按钮
    videoEventLayout->addWidget(pauseBtn);
    videoEventLayout->addWidget(playBtn);
    videoEventLayout->addWidget(photoBtn);
    // 设置布局的间距
    videoEventLayout->setContentsMargins(5, 5, 5, 5); // 左 上 右 下
    videoEventLayout->setSpacing(10); // 设置控件之间的间隔

}

// 连接信号和槽函数
void VideoEventView::initConnections()
{
    // 连接按钮点击信号到统一的槽函数
    connect(pauseBtn, &QPushButton::clicked, this, [=]() {
        emit VideoEventOperationRequested(VIDEO_PAUSE);
    });

    connect(playBtn, &QPushButton::clicked, this, [=]() {
        emit VideoEventOperationRequested(VIDEO_PLAY);
    });

    connect(photoBtn, &QPushButton::clicked, this, [=]() {
        emit VideoEventOperationRequested(VIDEO_PHOTO);
    });
}

