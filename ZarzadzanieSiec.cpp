#include "ZarzadzanieSiec.h"

ZarzadzanieSiec::ZarzadzanieSiec(QObject *parent)
    : QObject{parent}
{
    connect(&socket,&QTcpSocket::connected,this,&ZarzadzanieSiec::connected);
    connect(&socket,&QTcpSocket::disconnected,this,&ZarzadzanieSiec::disconnected);
    connect(&socket,&QTcpSocket::stateChanged,this,&ZarzadzanieSiec::socketStateChanged);
    connect(&socket,&QTcpSocket::errorOccurred,this,&ZarzadzanieSiec::errorOccurred);
    //connect(&socket,&QTcpSocket::readyRead,this,&ZarzadzanieSiec::socket_readyRead);
    connect(&socket, &QTcpSocket::readyRead, this, &ZarzadzanieSiec::OdbierzWiadomoscOdSerwera);

}

void ZarzadzanieSiec::connectToDevice(QString i, int p){
    // Sprawdzamy, czy socket jest otwarty, i czy adres i port są te same
    if(socket.isOpen()){
        if(ip == i && port == p){
            return; // Jeśli są te same, nic nie robimy
        }
        socket.close(); // Jeśli są inne, zamykamy połączenie
    }

    // Ustawiamy nowy adres i port
    ip = i;
    port = p;

    // Tworzymy obiekt QHostAddress z przekazanego adresu IP
    QHostAddress address(ip);
    if (address.isNull()) {
        qDebug() << "Niepoprawny adres IP:" << ip;
        return;
    }

    // Łączymy się z serwerem
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
    auto data =socket.readAll();
    emit dataReady(data);
}
void ZarzadzanieSiec::send(QString message){
    socket.write(message.toUtf8());
}

void ZarzadzanieSiec::WyslijWiadomoscDoSerwera(int nrRamki,StanSymulacji st,double intCzas,double warSter){

    if(socket.isOpen()){
        QByteArray wiadomosc;
        QDataStream out(&wiadomosc,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_6_8);

        out<<quint32(0);
        out<<nrRamki;
        out<<static_cast<quint8>(st);
        out<<intCzas;
        out<<warSter;
        qDebug() << "Klient wyslal ramkę:"
                 << "nrRamki =" << nrRamki
                 << ", stan =" << &st
                 << ", intCzas =" << intCzas
                 << ", warSter =" << warSter;
        out.device()->seek(0);
        out <<quint32(wiadomosc.size()-sizeof(quint32));
        socket.write(wiadomosc);
        socket.flush();


    }

}

void ZarzadzanieSiec::OdbierzWiadomoscOdSerwera() {
    bufor.append(socket.readAll());

    while (true) {
        if (dlugoscWiadomosci == 0) {
            if (bufor.size() < static_cast<int>(sizeof(quint32)))
                return;

            QDataStream sizeStream(&bufor, QIODevice::ReadOnly);
            sizeStream.setVersion(QDataStream::Qt_6_8);
            sizeStream >> dlugoscWiadomosci;
        }

        if (bufor.size() < static_cast<int>(dlugoscWiadomosci + sizeof(quint32)))
            return;

        QDataStream in(&bufor, QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_6_8);
        in.skipRawData(sizeof(quint32));

        int nrRamki;
        double wartoscReg;
        in >> nrRamki >> wartoscReg;

        emit daneSymulacji(nrRamki, wartoscReg);
        qDebug() << "Klient odebrał ramkę:" << nrRamki << wartoscReg;

        bufor.remove(0, sizeof(quint32) + dlugoscWiadomosci);
        dlugoscWiadomosci = 0;
    }
}

