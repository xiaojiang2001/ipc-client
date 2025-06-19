#ifndef CLIENTVIEW_H
#define CLIENTVIEW_H


#include <QWidget>
#include <QPushButton>
#include "radioBtnView.h"
#include "ptzView.h"
#include "videoEventView.h"

class ApplicationView : public QWidget
{
    Q_OBJECT
public:
    explicit ApplicationView(QWidget *parent = nullptr);
    ~ApplicationView();

    QWidget *getTopWidget()  { return topWidget; }
    QWidget *getVideoGridWidget()  { return videoGridWidget; }
    PTZView *getPTZView()  { return ptzWidget; }
    VideoEventView *getVideoEventView()  { return videoEventView; }
    RadioBtnView *getRadioBtnView()  { return radioBtnWidget; }

private:
    QWidget *topWidget;
    QWidget *videoGridWidget;
    PTZView *ptzWidget;
    VideoEventView *videoEventView;
    RadioBtnView *radioBtnWidget;


    void init_ptz_btn();

signals:

};

#endif // CLIENTVIEW_H
