#ifndef TCPSERWER_H
#define TCPSERWER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class TCPserwer : public QObject
{
    Q_OBJECT
public:
    explicit TCPserwer(QObject *parent = nullptr,quint16 p=12345);
    bool isStarted() const;
    void sendToAll(QString message);
    void UstawieniePortu(quint16 n);
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
    quint16 numerPortu;

};

#endif // TCPSERWER_H
