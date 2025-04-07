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
signals:


private slots:
    void on_client_connecting();

private:
    QTcpServer *serwer;
    QList<QTcpSocket *> socketList;
    bool _isStarted;

};

#endif // TCPSERWER_H
