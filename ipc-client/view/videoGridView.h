#ifndef VIDEOGRIDVIEW_H
#define VIDEOGRIDVIEW_H

#include <QWidget>
#include "widgetPool.h"
#include <QGridLayout>

class VideoGridView : public QWidget
{
    Q_OBJECT
public:
    explicit VideoGridView(QWidget *parent = nullptr);
    ~VideoGridView();

    void switchDisplayMode(int mode);                               // 切换显示模式
signals:


public slots:
    // 这里可以添加槽函数，例如处理视频网格的更新等
    void handlerGridViewChanged(int mode); // 显示模式改变信号

private:
    // 这里可以添加信号，例如视频网格的更新信号等

    // 你可以在这里定义一个窗口对象池来管理视频网格中的窗口

    widgetPool<QWidget> *videoGridViewPool; // 假设每个视频网格都是QWidget类型

    // // 其他私有成员函数和变量可以在这里定义
    void initUI();          // 初始化UI
    void initConnections(); // 初始化信号和槽连接       
    void updateVideoGrid(); // 更新视频网格显示

    QGridLayout *gridViewLayout; // 网格布局
    int gridRows;        // 网格行数
    int gridColumns;     // 网格列数
    int gridSpacing;     // 网格间距
    int gridMargin;      // 网格边距

    void resetLayout(int newRows, int newColumns);   // 重置布局
};

#endif // VIDEOGRIDVIEW_H
