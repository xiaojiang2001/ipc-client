#ifndef PTZVIEW_H
#define PTZVIEW_H

#include <QWidget>
#include <QPushButton>  

class PTZView : public QWidget
{
    Q_OBJECT
public:
    explicit PTZView(QWidget *parent = nullptr);
    ~PTZView();


private:    // control_btn
    QPushButton *okBtn;         // 确认按钮
    QPushButton *ptzUpBtn;      // ptzUp
    QPushButton *ptzDownBtn;    // ptzDown
    QPushButton *ptzLeftBtn;    // ptzLeft
    QPushButton *ptzRightBtn;   // ptzRight
signals:

};

#endif // PTZVIEW_H
