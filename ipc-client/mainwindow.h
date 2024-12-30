#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "videoplayer.h"
#include <QQueue>
#include <QImage>
#include <QPaintEvent>
#include "videowidget.h"

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

    void init_gridView();

    VideoPlayer *mplayer;
    QQueue<QImage> que;
    int camcaeWay;



    QWidget *widgetView1;
    QWidget *widgetView4;
    QWidget *widgetView9;
    QWidget *widgetView16;
    QVector<QWidget*> widgetView4Array;
    QVector<QWidget*> widgetView9Array;
    QVector<QWidget*> widgetView16Array;
    int showViewNum;
            
protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void slotGetOneImage(QImage image);
    void thread_func1();

    void on_radioBtn1_clicked();
    void on_radioBtn2_clicked();
    void on_radioBtn3_clicked();
    void on_radioBtn4_clicked();

    void showContextMenu(const QPoint &pos);

signals:
    void addViewNum();
};
#endif // MAINWINDOW_H
