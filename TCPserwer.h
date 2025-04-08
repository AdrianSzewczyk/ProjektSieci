#ifndef TCPSERWER_H
#define TCPSERWER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class TCPserwer : public QObject
{
    Q_OBJECT
public:
    explicit TCPserwer(QObject *parent = nullptr);
    bool isStarted() const;
    void sendToAll(QString message);
signals:
    void newClientConnected();
    void clientDisconnect();
    void dataReceived(QString message);

private slots:
    void on_client_connecting();
    void clientDisconnected();
    void clientDataRead();

private:
    QTcpServer *serwer;
    QList<QTcpSocket *> socketList;
    bool _isStarted;

};

#endif // TCPSERWER_H
