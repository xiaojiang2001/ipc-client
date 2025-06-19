#include "videoGridView.h"
#include <QPushButton>
#include <QDebug>
#include <QLabel>

VideoGridView::VideoGridView(QWidget *parent) : QWidget(parent)
{
    initUI();               // 初始化UI
    initConnections();      // 初始化信号和槽连接
}

// 析构函数
VideoGridView::~VideoGridView()
{
    delete videoGridViewPool; // 释放窗口对象池
}

// 初始化UI
void VideoGridView::initUI()
{
   gridRows = 4;        // 网格行数
   gridColumns = 4;     // 网格列数
   gridSpacing = 5;     // 网格间距
   gridMargin = 5;      // 网格边距

    gridViewLayout = new QGridLayout(this);
    setLayout(gridViewLayout); // 设置当前窗口的布局为网格布局


    gridViewLayout->setSpacing(gridSpacing);     // 设置控件之间的间隔
    gridViewLayout->setContentsMargins(gridMargin, gridMargin, gridMargin, gridMargin); // 设置网格布局的边距

    // 创建一个窗口对象池，用于管理视频网格中的窗口
    videoGridViewPool = new widgetPool<QWidget>(16, this);
    switchDisplayMode(16); // 初始化时使用16分屏模式
    // switchDisplayMode(9); // 初始化时使用16分屏模式
    // // 添加行和列
    // for (int row = 0; row < gridRows; ++row) {
    //    for (int col = 0; col < gridColumns; ++col) {
    //       QWidget *widget = videoGridViewPool->acquire(this); // 从池中获取一个窗口对象
    //       if (widget) {
    //           gridViewLayout->addWidget(widget, row, col); // 将窗口对象添加到网格布局中
    //       }
    //   }
    // }
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
                QWidget* widget = gridViewLayout->itemAtPosition(row, col)->widget();
                if (widget) {
                    gridViewLayout->removeWidget(widget);
                    videoGridViewPool->release(widget);     // 将widget归还到对象池
                }
            }
        }
    }

    // 3. 使用新的尺寸重新布局
    gridRows = newRows;
    gridColumns = newColumns;

    // 4. 添加新的widgets
    for (int row = 0; row < newRows; ++row) {
        for (int col = 0; col < newColumns; ++col) {
            QWidget* widget = videoGridViewPool->acquire(this);
            if (widget) {
                gridViewLayout->addWidget(widget, row, col);
            }
        }
    }

    // 5. 更新布局
    update();
}
