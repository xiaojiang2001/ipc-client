#include "ptzView.h"
#include <QGridLayout>
#include <QDebug>

PTZView::PTZView(QWidget *parent) : QWidget(parent)
{
    initUI();
    initConnections();
}

PTZView::~PTZView()
{

}

void PTZView::initUI()
{
    okBtn  = new QPushButton("ok",this);
    ptzUpBtn = new QPushButton("up",this);
    ptzDownBtn = new QPushButton("down",this);
    ptzLeftBtn = new QPushButton("left",this);
    ptzRightBtn = new QPushButton("right",this);
    okBtn->setMinimumSize(50,35);
    ptzUpBtn->setMinimumSize(50,35);
    ptzDownBtn->setMinimumSize(50,35);
    ptzLeftBtn->setMinimumSize(50,35);
    ptzRightBtn->setMinimumSize(50,35);

    // 网格布局
    QGridLayout *ptzLayout = new QGridLayout(this);
    ptzLayout->setSpacing(5);     //  设置控件之间的间隔
    //网格不同坐标添加不同的组件
    ptzLayout->addWidget(okBtn, 1, 1);
    ptzLayout->addWidget(ptzUpBtn, 0, 1);
    ptzLayout->addWidget(ptzDownBtn, 2, 1);
    ptzLayout->addWidget(ptzLeftBtn, 1, 0);
    ptzLayout->addWidget(ptzRightBtn, 1, 2);
}

void PTZView::initConnections()
{
    // 如何让 PTZView窗口发出信号
    // 连接按钮点击信号到统一的槽函数
    connect(ptzUpBtn, &QPushButton::clicked, this, [=]() {
        emit ptzOperationRequested(PTZ_UP);
    });

    connect(ptzDownBtn, &QPushButton::clicked, this, [=]() {
        emit ptzOperationRequested(PTZ_DOWN);
    });

    connect(ptzLeftBtn, &QPushButton::clicked, this, [=]() {
        emit ptzOperationRequested(PTZ_LEFT);
    });

    connect(ptzRightBtn, &QPushButton::clicked, this, [=]() {
        emit ptzOperationRequested(PTZ_RIGHT);
    });

    connect(okBtn, &QPushButton::clicked, this, [=]() {
        emit ptzOperationRequested(PTZ_OK);
    });
}
