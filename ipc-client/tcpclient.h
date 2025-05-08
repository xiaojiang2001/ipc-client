#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTimer>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);
    ~TcpClient();

    void connectToServer(const QString &host, quint16 port);
    void disconnectFromServer();
    int sendData(const QByteArray &data);
    
signals:
    void connected();
    void disconnected();
    void dataReceived(const QByteArray &data);
    void errorOccurred(const QString &errorString);


    private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();

private:
    QTimer *timer;  // 定时器对象
    void processData(const QByteArray &data);
    
    QTcpSocket *socket;
    QString serverHost;
    quint16 serverPort;

    
    void timeoutHandler();

};

#endif // TCPCLIENT_H
