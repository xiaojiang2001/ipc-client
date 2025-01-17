#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "videoplayer.h"
#include <QQueue>
#include <QVector>
#include <QImage>
#include <QPaintEvent>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // 播放器
    VideoPlayer *mplayer;       

    void init_gridView();       // 初始化gridView
    void init_control_btn();    // 初始化控制按钮
    bool m_pause_flag;          // 暂停标志

    // 保存图片
    void saveImageToJPEG(QImage image, QString name);   

    // 定义一个vector数组 数组的每一项为一个队列, 数组大小为16
    QVector<QQueue<QImage>> queArray;   // 存储16个队列
    //保存视频队列
    QQueue<QImage> saveQue;

    int camcaeWay;                      // 显示路数1 4 9 16
    int showViewNum;                    // 显示的视图数量

    // 在某个特定的窗口上绘制图像
    void paintImage(QPainter &painter, QWidget* widget, QImage &img);



    QWidget *widgetView1;
    QWidget *widgetView4;
    QWidget *widgetView9;
    QWidget *widgetView16;
    QVector<QWidget*> widgetView4Array;
    QVector<QWidget*> widgetView9Array;
    QVector<QWidget*> widgetView16Array;
    

    // control_btn
    QPushButton *pauseBtn;      // 暂停按钮
    QPushButton *playBtn;       // 播放按钮
    QPushButton *photoBtn;      // 拍照按钮
    QPushButton *startBtn;      // 录屏按钮
    QPushButton *stopBtn;       // 结束录屏按钮
            
protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void slotGetOneImage(int idx, QImage image);

    void on_radioBtn1_clicked();
    void on_radioBtn2_clicked();
    void on_radioBtn3_clicked();
    void on_radioBtn4_clicked();

    // 控制按钮
    void on_pauseBtn_clicked();
    void on_replayBtn_clicked();
    void on_photoBtn_clicked();
    void on_startBtn_clicked();
    void on_stopBtn_clicked();

    void showContextMenu(const QPoint &pos);


    void on_errorOccurred(const QString &errorMessage);
    
signals:
    void addViewNum(int index);
    void pauseSignal();
    void playSignal();
    void recordSignal(int flag);
};
#endif // MAINWINDOW_H
