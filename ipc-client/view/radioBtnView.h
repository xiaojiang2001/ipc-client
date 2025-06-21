#ifndef RADIOBTNVIEW_H
#define RADIOBTNVIEW_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QButtonGroup>
#include "global.h"

class RadioBtnView : public QWidget
{
    Q_OBJECT
public:
    explicit RadioBtnView(QWidget *parent = nullptr);
    ~RadioBtnView();

signals:
    void radioBtnClicked(int grid);     // 信号，当单选按钮被点击时发出


private:
    QLabel *label;
    QButtonGroup *radioBtnGroup;

    void initRadioButtons();

private slots:
    void onButtonGroupClicked(int id);  // 处理按钮组的点击


};

#endif // RADIOBTNVIEW_H
