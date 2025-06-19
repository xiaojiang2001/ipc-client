#include "viewController.h"
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
    connect(m_view->getRadioBtnView(), &RadioBtnView::radioBtnClicked, this, &Controller::handleRadioBtnClicked);
    connect(m_view->getPTZView(), &PTZView::ptzOperationRequested, this, &Controller::handlePTZOperation);
    connect(m_view->getVideoEventView(), &VideoEventView::VideoEventOperationRequested, this, &Controller::handleVideoEventOperation);
}

// 处理radio按钮点击事件
void Controller::handleRadioBtnClicked(int grid)
{
    qDebug() << "Radio button clicked with grid value:" << grid;
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