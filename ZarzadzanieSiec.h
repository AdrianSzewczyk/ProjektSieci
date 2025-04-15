#ifndef ZARZADZANIESIEC_H
#define ZARZADZANIESIEC_H

#include <QObject>
#include <QTcpSocket>

class ZarzadzanieSiec : public QObject
{
    Q_OBJECT
public:
    explicit ZarzadzanieSiec(QObject *parent = nullptr);
    void connectToDevice(QString i, int p);
    void disconnect();
    QAbstractSocket::SocketState state();
    bool isConnected();
    void send(QString message);
signals:
    void connected();
    void disconnected();
    void stateChanged(QAbstractSocket::SocketState);
    void errorOccurred(QAbstractSocket::SocketError);
    void dataReady(QByteArray);

private slots:
    void socketStateChanged(QAbstractSocket::SocketState state);
    void socket_readyRead();

private:
    QTcpSocket socket;
    QString ip;
    int port;

};

#endif // ZARZADZANIESIEC_H
