#ifndef TCPSERWER_H
#define TCPSERWER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "ZarzadzanieSiec.h"

class TCPserwer : public QObject
{
    Q_OBJECT
public:
    explicit TCPserwer(QObject *parent = nullptr,quint16 p=12345);
    ~TCPserwer();
    bool isStarted() const;
    void UstawieniePortu(quint16 n);
    void WyslijWiadomoscDoKlienta(int nrRamki,double warReg);
    void OdbierzWiadomoscOdKlienta();
    void setNrRamki();
    void AdresIport(QString &adr,quint16 &por);
    bool sprawdzenieSerwera(quint16 po);
    void close();
signals:
    void newClientConnected();
    void clientDisconnect();
    void dataReceived(QString message);
    void daneDoPrzetworzenia(int nrRamki,StanSymulacji s,double i, double w,double wZ);
    void errorOccurred(QAbstractSocket::SocketError);

private slots:
    void on_client_connecting();
    void clientDisconnected();
    void clientDataRead();

private:
    QTcpServer *serwer;
    QTcpSocket *klient;
    bool _isStarted;
    quint16 numerPortu;
    //QTcpSocket socket;

    QByteArray bufor;
    quint32 dlugosc;
    int nrRamki;

};

#endif // TCPSERWER_H
