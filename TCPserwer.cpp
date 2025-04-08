#include "TCPserwer.h"

TCPserwer::TCPserwer(QObject *parent)
    : QObject{parent}
{

    serwer = new QTcpServer(this);
    connect(serwer,&QTcpServer::newConnection,this,&TCPserwer::on_client_connecting);
    _isStarted = serwer->listen(QHostAddress::Any,12345);
    if(!_isStarted){
        qDebug()<<"Serwer nie wystartował";
    }else{
        qDebug()<<"Serwer wystartował";
    }

}
void TCPserwer::on_client_connecting(){

    qDebug()<<"Klient jest połączony z serwerem";
    auto socket = serwer->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this,&TCPserwer::clientDataRead);
    //connect(socket, &QTcpSocket::readyRead, this,&TCPserwer::clientDisconnected);
    connect(socket, &QTcpSocket::disconnected, this, [socket]() {
        QByteArray dane = socket->readAll();
        qDebug() << "Wiadomość od klienta:" << dane;
    });
    socketList.append(socket);
    socket->write("Siema na serwerze ziomal");
    emit newClientConnected();
}
bool TCPserwer::isStarted()const{
    return _isStarted;
}
void TCPserwer::sendToAll(QString message)
{
    foreach(auto socket, socketList)
    {
        socket->write(message.toUtf8());
    }
}

void TCPserwer::clientDisconnected(){
    emit clientDisconnect();
}
void TCPserwer::clientDataRead(){
    auto socket =qobject_cast<QTcpSocket*>(sender());
    auto data = socket->readAll();
    emit dataReceived(QString(data));
}

