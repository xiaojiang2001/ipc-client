#include "applicationView.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QButtonGroup>
#include <QRadioButton>

#include "QDebug"

ApplicationView::ApplicationView(QWidget *parent) : QWidget(parent)
{
    setupUI();          // 设置UI界面
    setupConnections(); // 设置信号和槽连接
}


ApplicationView::~ApplicationView()
{

}

// 设置UI界面
void ApplicationView::setupUI()
{
    // 创建垂直布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 通用的边框样式
    QString borderStyle = "border: 2px solid blue; border-radius: 5px; padding: 5px;";
    QString borderStyle2 = "border: 2px solid red; border-radius: 5px; padding: 5px;";

    // 创建多个 widget 容器并添加到垂直布局中
    topWidget = new QWidget(this);
    QWidget *middleWidget = new QWidget(this);
    QWidget *ptzEventWidget = new QWidget(this);
    videoGridWidget = new VideoGridView(this);
    ptzWidget = new PTZView(this);
    videoEventView = new VideoEventView(this);
    radioBtnWidget = new RadioBtnView(this);

    topWidget->setStyleSheet(borderStyle);
    middleWidget->setStyleSheet(borderStyle);
    videoGridWidget->setStyleSheet(borderStyle2);
    ptzEventWidget->setStyleSheet(borderStyle);
    ptzWidget->setStyleSheet(borderStyle);
    videoEventView->setStyleSheet(borderStyle);
    radioBtnWidget->setStyleSheet(borderStyle);

    mainLayout->addWidget(topWidget,10);
    mainLayout->addWidget(middleWidget,25);
    mainLayout->addWidget(radioBtnWidget,2);

    // 设置布局的间距
    mainLayout->setSpacing(10);     // 间隔
    mainLayout->setContentsMargins(10, 10, 10, 10);     //左 上 右 下

    // 为middleWidget创建水平布局
    QHBoxLayout *middleLayout = new QHBoxLayout(middleWidget);
    // 创建和添加Label 
    middleLayout->addWidget(videoGridWidget, 5);
    middleLayout->addWidget(ptzEventWidget, 1);

    // 为ptzEventWidget创建垂直布局
    QVBoxLayout *ptzEventLayout = new QVBoxLayout(ptzEventWidget);
    ptzEventLayout->addWidget(ptzWidget);
    ptzEventLayout->addWidget(videoEventView);
}

void ApplicationView::setupConnections()
{
    // 设置信号和槽连接

}