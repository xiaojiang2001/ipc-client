#ifndef CLIENTVIEW_H
#define CLIENTVIEW_H

#include <QObject>

class ClientView : public QObject
{
    Q_OBJECT
public:
    explicit ClientView(QObject *parent = nullptr);

signals:

};

#endif // CLIENTVIEW_H
