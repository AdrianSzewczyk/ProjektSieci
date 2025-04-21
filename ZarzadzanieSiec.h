#ifndef ZARZADZANIESIEC_H
#define ZARZADZANIESIEC_H

#include <QObject>
#include <QTcpSocket>

enum class StanSymulacji:quint8{
    Start,
    Stop,
    Reset
};

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
    void WyslijWiadomoscDoSerwera(int nrRamki,StanSymulacji st,double intCzas,double warSter);
    void OdbierzWiadomoscOdSerwera();

    void UstawPolaczenia();
    void RozłączPolaczenia();
signals:
    void connected();
    void disconnected();
    void stateChanged(QAbstractSocket::SocketState);
    void errorOccurred(QAbstractSocket::SocketError);
    void dataReady(QByteArray);
    void daneSymulacji(int n,double w);

private slots:
    void socketStateChanged(QAbstractSocket::SocketState state);
    void socket_readyRead();


private:
    QTcpSocket socket;
    QString ip;
    int port;
    QByteArray bufor;
    quint32 dlugoscWiadomosci=0;

};

#endif // ZARZADZANIESIEC_H
