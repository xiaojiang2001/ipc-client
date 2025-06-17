#include "applicationView.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QButtonGroup>
#include <QRadioButton>
#include "radioBtnView.h"
#include "ptzView.h"
#include "videoEventView.h"

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

/*
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
    viewLayout->addWidget(widgetView, 3);   // 占4份
    viewLayout->addWidget(widgetPTZ, 1);    // 占1份

    // 设置布局的间距
    viewLayout->setSpacing(10);
    viewLayout->setContentsMargins(5, 5, 5, 5);
*/
    // init_data_lable();
    // init_ptz_btn();
}


ApplicationView::~ApplicationView()
{

}


void ApplicationView::init_ptz_btn()
{





    // // 网格布局
    // QGridLayout *ptzLayout = new QGridLayout;
    // ptzLayout->setSpacing(5);     //  设置控件之间的间隔
    // //网格不同坐标添加不同的组件
    // ptzLayout->addWidget(pauseBtn, 0, 0);
    // ptzLayout->addWidget(playBtn,  0, 1);
    // ptzLayout->addWidget(photoBtn, 1, 0);
    // ptzLayout->addWidget(okBtn, 1, 1);
    // ptzLayout->addWidget(ptzUpBtn, 2, 0);
    // ptzLayout->addWidget(ptzDownBtn, 2, 1);
    // ptzLayout->addWidget(ptzLeftBtn, 3, 0);
    // ptzLayout->addWidget(ptzRightBtn, 3, 1);

    // widgetPTZ->setLayout(ptzLayout);
}
