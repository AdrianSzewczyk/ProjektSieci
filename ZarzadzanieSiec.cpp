#include "ZarzadzanieSiec.h"

ZarzadzanieSiec::ZarzadzanieSiec(QObject *parent)
    : QObject{parent}
{
    connect(&socket,&QTcpSocket::connected,this,&ZarzadzanieSiec::connected);
    connect(&socket,&QTcpSocket::disconnected,this,&ZarzadzanieSiec::disconnected);
    connect(&socket,&QTcpSocket::stateChanged,this,&ZarzadzanieSiec::socketStateChanged);
    connect(&socket,&QTcpSocket::errorOccurred,this,&ZarzadzanieSiec::errorOccurred);
    connect(&socket,&QTcpSocket::readyRead,this,&ZarzadzanieSiec::socket_readyRead);
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
