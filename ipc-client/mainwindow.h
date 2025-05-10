#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "videoplayer.h"
#include <QQueue>
#include <QVector>
#include <QImage>
#include <QPaintEvent>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "tcpclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int camcaeWay;                      // 显示路数1 4 9 16
private:
    Ui::MainWindow *ui;

    // 播放器
    VideoPlayer *mplayer;       

    void init_gridView();       // 初始化gridView
    void init_control_btn();    // 初始化控制按钮
    void init_data_lable();     // 初始化数据标签
    bool m_pause_flag;          // 暂停标志

    // 保存图片
    void saveImageToJPEG(QImage image, QString name);   

    // 定义一个vector数组 数组的每一项为一个队列, 数组大小为16
    QVector<QQueue<QImage>> queArray;   // 存储16个队列
    //保存视频队列
    QQueue<QImage> saveQue;


    int showViewNum;                    // 显示的视图数量

    QImage tempImage;

    // 在某个特定的窗口上绘制图像
    void paintImage(QPainter &painter, QWidget* widget, QImage &img);

    TcpClient *client;


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
    QPushButton *led1btn;
    QPushButton *led2btn;
    QPushButton *led3btn;

    // 显示标签
    QLabel *label_co2;
    QLabel *label_tempature;
    QLabel *label_humidity;
    QLabel *label_light;    
    QLineEdit *lineEdit_co2;
    QLineEdit *lineEdit_tempature;
    QLineEdit *lineEdit_humidity;
    QLineEdit *lineEdit_light;
    
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
    void on_led1btn_clicked();
    void on_led2btn_clicked();
    void on_led3btn_clicked();

    void showContextMenu(const QPoint &pos);


    void on_errorOccurred(const QString &errorMessage);

    void on_tcpReadyDateHadler(const QByteArray &data);

signals:
    void addViewNum(int index);
    void pauseSignal();
    void playSignal();
    void recordSignal(int flag);
};
#endif // MAINWINDOW_H
