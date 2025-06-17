#include "ptzView.h"
#include <QGridLayout>

PTZView::PTZView(QWidget *parent) : QWidget(parent)
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
    // ptzLayout->setColumnStretch(0, 1); // 设置列的伸缩因子
    // ptzLayout->setColumnStretch(1, 2); // 设置列的伸缩因子
    // ptzLayout->setColumnStretch(2, 1); // 设置列的伸缩因子
    // ptzLayout->setRowStretch(0, 1);    // 设置行的伸缩因子

}

PTZView::~PTZView()
{

}