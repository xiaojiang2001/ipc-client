#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QWidget>

class Model : public QWidget
{
    Q_OBJECT
public:
    explicit Model(QWidget *parent = nullptr);

signals:

};

#endif // MODEL_H
