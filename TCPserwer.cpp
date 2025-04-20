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
    klient = serwer->nextPendingConnection();

    connect(klient, &QTcpSocket::readyRead, this, &TCPserwer::OdbierzWiadomoscOdKlienta);
    connect(klient, &QTcpSocket::disconnected, this, &TCPserwer::clientDisconnected);

    klient->write("Siema na serwerze ziomal");
    emit newClientConnected();
}

bool TCPserwer::isStarted()const{
    return _isStarted;
}
void TCPserwer::sendToAll(QString message)
{
    //foreach(auto socket, socketList)
   // {
  //  auto socket;
    //    socket->write(message.toUtf8());
   // }
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
    qDebug() << "Serwer próbuje wysłać ramkę:" << nrRamki << warReg;
    if (!klient) {
        qDebug() << "Brak klienta do wysyłki!";
        return;
    }

    QByteArray wiadomosc;
    QDataStream out(&wiadomosc, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_8);
    out << quint32(0) << nrRamki << warReg;
    out.device()->seek(0);
    out << quint32(wiadomosc.size() - sizeof(quint32));

    klient->write(wiadomosc);
    klient->flush();

    qDebug() << "Serwer wysłał ramkę:" << nrRamki << warReg;
}


void TCPserwer::OdbierzWiadomoscOdKlienta() {
    if (!klient) return;

    bufor.append(klient->readAll());
    QDataStream in(&bufor, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_6_8);

    while (true) {
        if (dlugosc == 0) {
            if (bufor.size() < static_cast<int>(sizeof(quint32)))
                return;

            in >> dlugosc;
        }

        if (bufor.size() < static_cast<int>(dlugosc + sizeof(quint32)))
            return;

        int nrRamki;
        quint8 stanSym;
        double intCzas;
        double wartoscSterujaca;

        in >> nrRamki >> stanSym >> intCzas >> wartoscSterujaca;

        // Emit danych
        StanSymulacji stan = static_cast<StanSymulacji>(stanSym);
        qDebug() << "Serwer odebrał ramkę:" << nrRamki << &stan << intCzas << wartoscSterujaca;
        emit daneDoPrzetworzenia(nrRamki, stan, intCzas, wartoscSterujaca);

        // Usuń przetworzone bajty
        bufor.remove(0, dlugosc + sizeof(quint32));
        dlugosc = 0;
    }
}

