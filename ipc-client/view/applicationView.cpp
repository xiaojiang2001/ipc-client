#include "applicationView.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QButtonGroup>
#include <QRadioButton>

#include "QDebug"

ApplicationView::ApplicationView(QWidget *parent) : QWidget(parent)
{
    // 创建垂直布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 通用的边框样式
    QString borderStyle = "border: 2px solid blue; border-radius: 5px; padding: 5px;";

    // 创建多个 widget 容器并添加到垂直布局中
    topWidget = new QWidget();
    QWidget *middleWidget = new QWidget();
    QWidget *ptzEventWidget = new QWidget();
    videoGridWidget = new QWidget();
    ptzWidget = new PTZView();
    videoEventView = new VideoEventView();
    radioBtnWidget = new RadioBtnView(this);

    topWidget->setStyleSheet(borderStyle);
    middleWidget->setStyleSheet(borderStyle);
    ptzEventWidget->setStyleSheet(borderStyle);
    videoGridWidget->setStyleSheet(borderStyle);
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
    middleLayout->addWidget(ptzEventWidget,1);

    // 为ptzEventWidget创建垂直布局
    QVBoxLayout *ptzEventLayout = new QVBoxLayout(ptzEventWidget);
    ptzEventLayout->addWidget(ptzWidget);
    ptzEventLayout->addWidget(videoEventView);

    // connect(radioBtnWidget, &RadioBtnView::radioBtnClicked, 
    //                 this, [=] {
    //             qDebug() << "控制器接收到信号:";
    // });
}


ApplicationView::~ApplicationView()
{

}


void ApplicationView::init_ptz_btn()
{
    
}
