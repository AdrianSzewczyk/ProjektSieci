#include "ZarzadzanieSiec.h"

ZarzadzanieSiec::ZarzadzanieSiec(QObject *parent)
    : QObject{parent}
{
    connect(&socket,&QTcpSocket::connected,this,&ZarzadzanieSiec::connected);
    connect(&socket,&QTcpSocket::disconnected,this,&ZarzadzanieSiec::disconnected);
    connect(&socket,&QTcpSocket::errorOccurred,this,&ZarzadzanieSiec::errorOccurred);

}

void ZarzadzanieSiec::connectToDevice(QString i, int p){
    if(socket.isOpen()){
        if(ip == i && port == p){
            return;
        }
        socket.close();
    }
    ip = i;
    port = p;

    QHostAddress address(ip);
    if (address.isNull()) {
        qDebug() << "Niepoprawny adres IP:" << ip;
        return;
    }
    socket.connectToHost(address, port);
}
void ZarzadzanieSiec::socketStateChanged(QAbstractSocket::SocketState state){
    if(state == QAbstractSocket::UnconnectedState){
        socket.close();
    }
    emit stateChanged(state);
}

QAbstractSocket::SocketState ZarzadzanieSiec::state(){
    return socket.state();
}
void ZarzadzanieSiec::disconnect(){
    socket.close();
}
bool ZarzadzanieSiec::isConnected(){
    return socket.state() == QAbstractSocket::ConnectedState;
}
void ZarzadzanieSiec::socket_readyRead(){
    OdbierzWiadomoscOdSerwera();
}
void ZarzadzanieSiec::send(QString message){
    socket.write(message.toUtf8());
}

void ZarzadzanieSiec::WyslijWiadomoscDoSerwera(int nrRamki,StanSymulacji st,double intCzas,double warSter,double wZ){

    if(socket.isOpen()){
        QByteArray wiadomosc;
        QDataStream out(&wiadomosc,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_6_5);

        out<<quint32(0);
        out<<nrRamki;
        out<<static_cast<quint8>(st);
        out<<intCzas;
        out<<warSter;
        out<<wZ;

        if (!socket.isValid()) {
            qDebug() << "[BŁĄD] Socket jest nieprawidłowy!";
            return;
        }
        out.device()->seek(0);
        out <<quint32(wiadomosc.size()-sizeof(quint32));
        socket.write(wiadomosc);
        socket.flush();
    }
}
void ZarzadzanieSiec::OdbierzWiadomoscOdSerwera() {
    bufor.append(socket.readAll());

    QDataStream in(&bufor, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_6_5);

    while (true) {
        const int headerSize = sizeof(quint32);
        if (bufor.size() < headerSize) {
            return;
        }

        in.device()->seek(0);
        quint32 dlugoscWiadomosci = 0;
        in >> dlugoscWiadomosci;
        if (bufor.size() < headerSize + static_cast<int>(dlugoscWiadomosci)) {
            return;
        }
        int nrRamki;
        double wartoscReg;
        in >> nrRamki >> wartoscReg;
        emit daneSymulacji(nrRamki, wartoscReg);
        bufor.remove(0, headerSize + static_cast<int>(dlugoscWiadomosci));
    }
}

void ZarzadzanieSiec::UstawPolaczenia() {
    connect(&socket, &QTcpSocket::readyRead, this, &ZarzadzanieSiec::OdbierzWiadomoscOdSerwera);
}
void ZarzadzanieSiec::RozłączPolaczenia(){
    QAbstractSocket::disconnect(&socket, &QTcpSocket::readyRead, this, &ZarzadzanieSiec::OdbierzWiadomoscOdSerwera);
}
void ZarzadzanieSiec::setNrRamki(){
    nrRamki=0;
}
