#include "TCPserwer.h"

TCPserwer::TCPserwer(QObject *parent, quint16 p)
    : QObject{parent},
    serwer(nullptr),
    klient(nullptr),
    _isStarted(false),
    numerPortu(p),
    dlugosc(0),
    nrRamki(0)
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
TCPserwer::~TCPserwer(){

}
void TCPserwer::on_client_connecting(){
    qDebug()<<"Klient jest połączony z serwerem";
    klient = serwer->nextPendingConnection();

    connect(klient, &QTcpSocket::readyRead, this, &TCPserwer::OdbierzWiadomoscOdKlienta);
    connect(klient, &QTcpSocket::disconnected, this, &TCPserwer::clientDisconnected);
    connect(klient,&QTcpSocket::errorOccurred,this,&TCPserwer::errorOccurred);
    emit newClientConnected();
}

bool TCPserwer::isStarted()const{
    return _isStarted;
}


void TCPserwer::clientDisconnected(){
     qDebug() << "Emit client disconnected";
    emit clientDisconnect();
}
void TCPserwer::clientDataRead(){
    auto socket =qobject_cast<QTcpSocket*>(sender());
    auto data = socket->readAll();
    qDebug() << "Emit data received";
    emit dataReceived(QString(data));
}
void TCPserwer::UstawieniePortu(quint16 n){

    numerPortu=n;
}

void TCPserwer::WyslijWiadomoscDoKlienta(int nrRamki,double warReg){
    if (!klient) {
        return;
    }

    QByteArray wiadomosc;
    QDataStream out(&wiadomosc, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    out << quint32(0) << nrRamki << warReg;
    out.device()->seek(0);
    out << quint32(wiadomosc.size() - sizeof(quint32));

    klient->write(wiadomosc);
    klient->flush();

    qDebug() << "Serwer wysłał ramkę:" << nrRamki << warReg;
}


void TCPserwer::OdbierzWiadomoscOdKlienta() {
    bufor.append( klient->readAll() );
    const int headerSize = sizeof(quint32);
    while (bufor.size() >= headerSize) {
        QDataStream headerStream(bufor);
        headerStream.setVersion(QDataStream::Qt_6_5);

        quint32 msgSize = 0;
        headerStream >> msgSize;
        if (msgSize == 0 || msgSize > 1024) {
            bufor.remove(0, headerSize);
            continue;
        }
        if (bufor.size() < headerSize + int(msgSize)) {
            break;
        }
        QByteArray payload = bufor.mid(headerSize, msgSize);
        QDataStream dataStream(&payload, QIODevice::ReadOnly);
        dataStream.setVersion(QDataStream::Qt_6_5);
        int     nrRamki;
        quint8  stanSym;
        double  intCzas, wartSter;
        double warZad;
        dataStream >> nrRamki >> stanSym >> intCzas >> wartSter>>warZad;

        StanSymulacji s = static_cast<StanSymulacji>(stanSym);
        emit daneDoPrzetworzenia(nrRamki, s, intCzas, wartSter,warZad);

        bufor.remove(0, headerSize + msgSize);
    }
}

void TCPserwer::setNrRamki(){
    nrRamki=0;
}

void TCPserwer::AdresIport(QString &adr,quint16 &por){
    adr = klient->peerAddress().toIPv4Address() ?
              QHostAddress(klient->peerAddress().toIPv4Address()).toString() :
              klient->peerAddress().toString();
    por=klient->peerPort();
}

bool TCPserwer::sprawdzenieSerwera(quint16 po){
    if (serwer->isListening()) {
        serwer->close();
    }
    _isStarted = serwer->listen(QHostAddress::Any, po);
    return _isStarted;
}

void TCPserwer::close()
{
    if (klient) {
        klient->disconnectFromHost();
        if (klient->state() != QAbstractSocket::UnconnectedState) {
            klient->waitForDisconnected(1000);
        }
        klient->deleteLater();
        klient = nullptr;
    }

    if (serwer->isListening()) {
        serwer->close();
    }
    _isStarted = false;
}
