#include "controller.h"
#include <QDebug>
#include <QTimer>
#include "radioBtnView.h"

Controller::Controller()
{
    
}

Controller::~Controller()
{
    // delete m_view;
    // delete m_model;
}

void Controller::initialize()
{
    if (!m_view || !m_model) {
        qWarning() << "视图或模型未设置";
        return;
    }

    initConnections();  // 在完全初始化后建立连接
}


void Controller::initConnections()
{
    // 确保视图和模型都已设置
    if (!m_view || !m_model) {
        qWarning() << "视图或模型未设置，无法初始化连接";
        return;
    }   
    

    // 连接视图和控制器之间的信号和槽 view to controller
    connect(m_view->getRadioBtnView(), &RadioBtnView::radioBtnClicked, this, &Controller::handleRadioBtnClicked);
    connect(m_view->getPTZView(), &PTZView::ptzOperationRequested, this, &Controller::handlePTZOperation);
    connect(m_view->getVideoEventView(), &VideoEventView::VideoEventOperationRequested, this, &Controller::handleVideoEventOperation);

    // 连接模型和视图之间的信号和槽 model to controller
    connect(m_model,&VideoEventController::sendImage, this , &Controller::GetOneImage);


    // 连接模型和视图之间的信号和槽 controller to view
    connect(this, &Controller::videoGridViewUpdated, m_view->getVideoGridView(), &VideoGridView::handlerGridViewChanged);
    connect(this,&Controller::GetOneImage, m_view->getVideoGridView() , &VideoGridView::updateVideo);

}

// 处理radio按钮点击事件
void Controller::handleRadioBtnClicked(int grid)
{
    // qDebug() << "Radio button clicked with grid value:" << grid;
    emit videoGridViewUpdated(grid);  // 发出视频网格更新信号
}


// 处理PTZ操作信号
void Controller::handlePTZOperation(PTZOperation operation)
{
    switch (operation) {
        case PTZ_UP:
            qDebug() << "PTZ 向上移动";
            // 处理向上移动
            break;
        case PTZ_DOWN:
            qDebug() << "PTZ 向下移动";
            // 处理向下移动
            break;
        case PTZ_LEFT:
            qDebug() << "PTZ 向左移动";
            // 处理向左移动
            break;
        case PTZ_RIGHT:
            qDebug() << "PTZ 向右移动";
            // 处理向右移动
            break;
        case PTZ_OK:
            qDebug() << "PTZ 确认";
            // 处理确认
            break;
    }
}

// 处理视频事件操作信号
void Controller::handleVideoEventOperation(VideoEventType operation)
{
    switch (operation) {
        case VIDEO_PAUSE:
            qDebug() << "视频暂停";
            // 处理视频暂停
            break;
        case VIDEO_PLAY:
            qDebug() << "视频播放";
            // 处理视频播放
            break;
        case VIDEO_PHOTO:
            qDebug() << "拍照";
            // 处理拍照
            break;
    }
}
