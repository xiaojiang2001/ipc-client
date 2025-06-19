#ifndef CLIENTVIEW_H
#define CLIENTVIEW_H


#include <QWidget>
#include <QPushButton>
#include "radioBtnView.h"
#include "ptzView.h"
#include "videoEventView.h"
#include "videoGridView.h"

class ApplicationView : public QWidget
{
    Q_OBJECT
public:
    explicit ApplicationView(QWidget *parent = nullptr);
    ~ApplicationView();

    QWidget *getTopWidget()  { return topWidget; }
    VideoGridView *getVideoGridView()  { return videoGridWidget; }
    PTZView *getPTZView()  { return ptzWidget; }
    VideoEventView *getVideoEventView()  { return videoEventView; }
    RadioBtnView *getRadioBtnView()  { return radioBtnWidget; }

private:
    void setupUI();
    void setupConnections();

    QWidget *topWidget;
    VideoGridView *videoGridWidget;
    PTZView *ptzWidget;
    VideoEventView *videoEventView;
    RadioBtnView *radioBtnWidget;

signals:

};

#endif // CLIENTVIEW_H
