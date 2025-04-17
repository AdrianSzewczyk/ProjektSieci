#include "TCPserwer.h"

TCPserwer::TCPserwer(QObject *parent, quint16 p)
    : QObject{parent}, numerPortu(p)
{

    serwer = new QTcpServer(this);
    connect(serwer,&QTcpServer::newConnection,this,&TCPserwer::on_client_connecting);
    _isStarted = serwer->listen(QHostAddress::Any,numerPortu);
    if(!_isStarted){
        qDebug()<<"Serwer nie wystartował";
    }else{
        qDebug()<<"Serwer wystartował";
    }

}
void TCPserwer::on_client_connecting(){

    qDebug()<<"Klient jest połączony z serwerem";
    auto socket = serwer->nextPendingConnection();
  //  connect(socket, &QTcpSocket::readyRead, this,&TCPserwer::clientDataRead);
    connect(socket, &QTcpSocket::readyRead, this, &TCPserwer::OdbierzWiadomoscOdKlienta);
    connect(socket, &QTcpSocket::disconnected, this,&TCPserwer::clientDisconnected);
    /*connect(socket, &QTcpSocket::disconnected, this, [socket]() {
        QByteArray dane = socket->readAll();
        qDebug() << "Wiadomość od klienta:" << dane;
    });*/
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
void TCPserwer::UstawieniePortu(quint16 n){

    numerPortu=n;
    //_isStarted = serwer->listen(QHostAddress::Any,numerPortu);
}

void TCPserwer::WyslijWiadomoscDoKlienta(int nrRamki,double warReg){
    auto socket = qobject_cast<QTcpSocket*>(sender());
    QByteArray wiadomosc;
    QDataStream out(&wiadomosc,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_8);
    out<<quint32(0);
    out<<nrRamki;
    out<<warReg;
    out.device()->seek(0);
    out<<quint32(wiadomosc.size()-sizeof(quint32));

    socket->write(wiadomosc);
    socket->flush();
}

void TCPserwer::OdbierzWiadomoscOdKlienta(){
    auto socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    bufory[socket].append(socket->readAll());

    QDataStream in(&bufory[socket], QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_6_8);

    while (true) {
        if (!dlugosci.contains(socket)) {
            dlugosci[socket] = 0;
        }

        // Sprawdzenie, czy możemy odczytać długość
        if (dlugosci[socket] == 0) {
            if (bufory[socket].size() < static_cast<int>(sizeof(quint32)))
                return;
            in >> dlugosci[socket];
        }

        // Czy mamy całą ramkę?
        if (bufory[socket].size() < static_cast<int>(dlugosci[socket] + sizeof(quint32)))
            return;

        // Odczytanie zawartości ramki
        int nrRamki;
        quint8 stanSym;
        double intCzas;
        double wartoscSterujaca;

        in >> nrRamki >> stanSym >> intCzas >> wartoscSterujaca;

        // Możesz rzutować jeśli masz enum np. StanSymulacji:
        StanSymulacji stan = static_cast<StanSymulacji>(stanSym);

        qDebug() << "Serwer odebrał ramkę:"
                 << "nrRamki =" << nrRamki
                 << ", stan =" << &stan
                 << ", intCzas =" << intCzas
                 << ", warSter =" << wartoscSterujaca;
        emit daneDoPrzetworzenia(nrRamki,stan ,intCzas, wartoscSterujaca);

    }


}
