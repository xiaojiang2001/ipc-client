#include "radioBtnView.h"
#include <QDebug>

RadioBtnView::RadioBtnView(QWidget *parent) : QWidget(parent)
{
    initRadioButtons();
    // 连接信号和槽
    connect(radioBtnGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), this, [this](int id) {
        qDebug() << "按钮ID:" << id;
        emit radioBtnClicked(id); // 发出信号
    });
}

RadioBtnView::~RadioBtnView()
{
    delete label;
    delete radioBtnGroup;
}

void RadioBtnView::initRadioButtons()
{
    QHBoxLayout *radioBtnLayout = new QHBoxLayout(this);

    // 创建标签
    label = new QLabel("view grid:", this);
    radioBtnLayout->addWidget(label);
    label->setStyleSheet("font-weight: bold; color: black;");

    // 创建按钮组
    radioBtnGroup = new QButtonGroup(this);
    radioBtnGroup->setExclusive(true); // 设置为互斥组

    // 创建多个单选按钮并添加到按钮组
    for (int i = 1; i <= 4; ++i) {
        QRadioButton *radioBtn = new QRadioButton(QString("%1").arg(i*i), this);
        radioBtnGroup->addButton(radioBtn, i * i); // 设置按钮ID
        radioBtnLayout->addWidget(radioBtn);
        if(i == 1)
            radioBtn->setChecked(true);  // 设置第一个按钮为选中状态
    }
    // 添加弹簧
    radioBtnLayout->addStretch();
}

