#include "TCPserwer.h"

TCPserwer::TCPserwer(QObject *parent)
    : QObject{parent}
{

    serwer = new QTcpServer(this);
    connect(serwer,&QTcpServer::newConnection,this,&TCPserwer::on_client_connecting);
    _isStarted - serwer->listen(QHostAddress::Any,12345);
    if(!_isStarted){
        qDebug()<<"Serwer nie wystartował";
    }else{
        qDebug()<<"Serwer wystartował";
    }

}
void TCPserwer::on_client_connecting(){

    qDebug()<<"Klient jest połączony z serwerem";
    auto socket = serwer->nextPendingConnection();
}
bool TCPserwer::isStarted()const{
    return _isStarted;
}
