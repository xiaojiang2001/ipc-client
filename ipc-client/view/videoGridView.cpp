#include "videoGridView.h"
#include <QPushButton>
#include <QDebug>
#include <QLabel>


VideoGridView::VideoGridView(QWidget *parent) : QWidget(parent)
{
    initUI();               // 初始化UI
    initConnections();      // 初始化信号和槽连接

//    isMaximized = false;
//    maximizedWidget = nullptr;
}

// 析构函数
VideoGridView::~VideoGridView()
{
    delete videoGridViewPool; // 释放窗口对象池
}

// 初始化UI
void VideoGridView::initUI()
{
   gridRows = INIT_GRID;        // 网格行数
   gridColumns = INIT_GRID;     // 网格列数
   gridSpacing = 5;             // 网格间距
   gridMargin = 5;              // 网格边距

    gridViewLayout = new QGridLayout(this);
    setLayout(gridViewLayout); // 设置当前窗口的布局为网格布局



    gridViewLayout->setSpacing(gridSpacing);     // 设置控件之间的间隔
    gridViewLayout->setContentsMargins(gridMargin, gridMargin, gridMargin, gridMargin); // 设置网格布局的边距

    // 创建一个窗口对象池，用于管理视频网格中的窗口
    videoGridViewPool = new widgetPool<VideoWidget>(16, this);
    switchDisplayMode(INIT_GRID * INIT_GRID); // 初始化时使用4分屏模式
}

void VideoGridView::initConnections()
{

}



// 处理显示模式改变的信号槽函数
void VideoGridView::handlerGridViewChanged(int mode)
{
    // qDebug() << "VideoGridView: Display mode changed to" << mode;
    switchDisplayMode(mode); // 切换显示模式
}


// 切换显示模式
void VideoGridView::switchDisplayMode(int mode) {
    int rows = 0, cols = 0;
    switch (mode) {
        case 1:  rows = cols = 1; break;
        case 4:  rows = cols = 2; break;
        case 9:  rows = cols = 3; break;
        case 16: rows = cols = 4; break;
        default: return;
    }
    resetLayout(rows, cols);
}


void VideoGridView::resetLayout(int newRows, int newColumns)
{
    // 1. 保存旧的尺寸
    int oldRows = gridRows;
    int oldColumns = gridColumns;

    // 2. 从布局中移除并回收所有widget
    if (gridViewLayout->count() > 0)
    {
        for (int row = 0; row < oldRows; ++row) {
            for (int col = 0; col < oldColumns; ++col) {
                VideoWidget* widget = qobject_cast<VideoWidget*>(gridViewLayout->itemAtPosition(row, col)->widget());
                if (widget) {
                disconnect(widget, &VideoWidget::doubleClicked, this, &VideoGridView::onWidgetDoubleClicked);
                gridViewLayout->removeWidget(widget);
                videoGridViewPool->release(widget);     // 将widget归还到对象池
                }
            }
        }
    }

    // 3. 使用新的尺寸重新布局
    gridRows = newRows;
    gridColumns = newColumns;

    int index = 0; // 用于设置窗口内容的索引
    // 4. 添加新的widgets
    for (int row = 0; row < newRows; ++row) {
        for (int col = 0; col < newColumns; ++col) {
            VideoWidget* widget = videoGridViewPool->acquire(this);
            if (widget) {
                gridViewLayout->addWidget(widget, row, col);
                connect(widget, &VideoWidget::doubleClicked, this, &VideoGridView::onWidgetDoubleClicked);
                 widget->setDisplayText(QString("窗口%1").arg(++index)); // 设置内容
            }
            else {
                qDebug() << "acquire failed!";
            }
        }
    }

    // 5. 更新布局
    update();
}

// 双击 新增槽函数
void VideoGridView::onWidgetDoubleClicked(VideoWidget* widget)
{
    if( gridViewLayout->count() < 4)
        return;

    static bool isMaximized = false;
    static VideoWidget* maximizedWidget = nullptr;


    if (!isMaximized) {
        // 第一次双击，放大
        for (int i = 0; i < gridViewLayout->count(); ++i) {
            QWidget* w = gridViewLayout->itemAt(i)->widget();
            if (w) w->setVisible(w == widget);
        }
        maximizedWidget = widget;
        isMaximized = true;
    } else {
        // 再次双击，恢复所有窗口
        for (int i = 0; i < gridViewLayout->count(); ++i) {
            QWidget* w = gridViewLayout->itemAt(i)->widget();
            if (w) w->setVisible(true);
        }
        maximizedWidget = nullptr;
        isMaximized = false;
    }

    // qDebug() << "VideoGridView: Widget double-clicked, switching display mode.";

    // // 简单实现：全屏显示该widget，其它隐藏
    //  for (int i = 0; i < gridViewLayout->count(); ++i) {
    //      QWidget* w = gridViewLayout->itemAt(i)->widget();
    //      if (w) w->setVisible(w == widget);
    //  }
    // 你也可以切换布局为1x1，或弹窗显示
}
