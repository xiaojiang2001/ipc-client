#include "tcpclient.h"
#include <QDebug>
#include <QAbstractSocket>
#include <QMessageBox>

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{

   socket = new QTcpSocket(this);

    // 连接信号槽
    connect(socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &TcpClient::onDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);


    // 定时器
    timer = new QTimer(this);
    // 启动定时器，每隔 5 秒触发一次
    timer->start(3000);  // 5000 毫秒 = 5 秒
    // 连接定时器的 timeout 信号到 sendData 槽
    connect(timer, &QTimer::timeout, this, &TcpClient::timeoutHandler);

}

// 发送数据的槽函数
void TcpClient::timeoutHandler()
{
    // qDebug() << " send test data";
    // sendData("test data from client\n");
}


TcpClient::~TcpClient()
{
    disconnectFromServer();
    if (socket) {
        socket->deleteLater();
    }
}

int TcpClient::sendData(const QByteArray &data) 
{
    if (!socket || socket->state() != QAbstractSocket::ConnectedState) {
        qDebug() << "Socket is not connected!";
        return -1; // 返回错误码，表示未连接
    }

    // 发送数据
    qint64 bytesWritten = socket->write(data);
    if (bytesWritten == -1) {
        qDebug() << "Failed to send data:" << socket->errorString();
        return -2; // 返回错误码，表示发送失败
    }

    // 确保数据被发送
    if (!socket->waitForBytesWritten(5000)) { // 等待 5 秒
        qDebug() << "Failed to wait for bytes written:" << socket->errorString();
        return -3; // 返回错误码，表示等待超时
    }

    qDebug() << "Data sent successfully, size:" << bytesWritten << "bytes";
    return static_cast<int>(bytesWritten); // 返回实际发送的字节数
}

void TcpClient::connectToServer(const QString &host, quint16 port)
{
    serverHost = host;
    serverPort = port;
    
    qDebug() << "Connecting to server..." << host << ":" << port;
    socket->connectToHost(host, port);
}

void TcpClient::disconnectFromServer()
{
    if (socket && socket->state() == QAbstractSocket::ConnectedState) {
        socket->disconnectFromHost();
         QMessageBox::information(nullptr, "断开连接", "断开连接成功!");
    }
}

void TcpClient::onConnected()
{
    qDebug() << "Connected to server!";

    // 最简单的信息提示框
    QMessageBox::information(nullptr, "连接成功", "成功连接到服务器!");


    emit connected();
}

void TcpClient::onDisconnected()
{
    qDebug() << "Disconnected from server!";
    emit disconnected();
}

void TcpClient::onReadyRead()
{
    // 读取所有可用数据
    QByteArray data = socket->readAll();
    // qDebug() << "Received data size:" << data.size() << "bytes";
    
    // 处理数据并发出信号
    // processData(data);
    emit dataReceived(data);
}

void TcpClient::processData(const QByteArray &data)
{
    // 在这里实现你的数据处理逻辑
    // 例如：解析协议、更新UI等
    // 这个示例只是简单打印数据
    // qDebug() << "Processing data:" << data;
}
