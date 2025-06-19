#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "singleton.h"
#include "applicationView.h"
#include "model.h"


class Controller : public QObject
{
    Q_OBJECT

public:

    void setView(ApplicationView* view) { m_view = view; }
    void setModel(Model* model) { m_model = model; }
    void initialize();


signals:
    void videoGridViewUpdated(int grid);                // 视频网格更新信号

public slots:
    void handleRadioBtnClicked(int grid);               // 处理radio按钮点击事件
    void handlePTZOperation(PTZOperation operation);    // 处理PTZ操作信号
    void handleVideoEventOperation(VideoEventType operation); // 处理视频事件操作信号

public:
    void initConnections();

private:
    ApplicationView* m_view;
    Model *m_model;

    SINGLETON(Controller)

};

#endif // CONTROLLER_H
