#ifndef PTZVIEW_H
#define PTZVIEW_H

#include <QWidget>
#include <QPushButton>  

// 定义枚举类型
enum PTZOperation {
    PTZ_UP,
    PTZ_DOWN,
    PTZ_LEFT,
    PTZ_RIGHT,
    PTZ_OK,
};
// Q_ENUM(PTZOperation)  // 注册枚举到元对象系统


class PTZView : public QWidget
{
    Q_OBJECT
public:
    explicit PTZView(QWidget *parent = nullptr);
    ~PTZView();



// signals
signals:
    // 统一的 PTZ 控制信号
    void ptzOperationRequested(PTZOperation operation);

private:

    void initUI();
    void initConnections();

    QPushButton *okBtn;         // 确认按钮
    QPushButton *ptzUpBtn;      // ptzUp
    QPushButton *ptzDownBtn;    // ptzDown
    QPushButton *ptzLeftBtn;    // ptzLeft
    QPushButton *ptzRightBtn;   // ptzRight

};

#endif // PTZVIEW_H
