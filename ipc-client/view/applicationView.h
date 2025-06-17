#ifndef CLIENTVIEW_H
#define CLIENTVIEW_H


#include <QWidget>
#include <QPushButton>

class ApplicationView : public QWidget
{
    Q_OBJECT
public:
    explicit ApplicationView(QWidget *parent = nullptr);
    ~ApplicationView();

private:
    QWidget *topWidget;
    QWidget *videoGridWidget;
    QWidget *ptzWidget;
    QWidget *videoEventView;
    QWidget *radioBtnWidget;


    void init_ptz_btn();

signals:

};

#endif // CLIENTVIEW_H
