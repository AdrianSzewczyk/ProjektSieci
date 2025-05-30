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
    //klient->setSocketOption(QAbstractSocket::ReuseAddressHint, 1);
    //serwer->setSocketOption(QAbstractSocket::ReuseAddressHint, 1);
    connect(serwer,&QTcpServer::newConnection,this,&TCPserwer::on_client_connecting);
    _isStarted = serwer->listen(QHostAddress::Any,numerPortu);
    if(!_isStarted){
        qDebug()<<"Serwer nie wystartował";
    }else{
        qDebug()<<"Serwer wystartował";
    }


}
TCPserwer::~TCPserwer(){
    //disconnect(klient, &QTcpSocket::readyRead, this, &TCPserwer::OdbierzWiadomoscOdKlienta);
   // disconnect(klient, &QTcpSocket::disconnected, this, &TCPserwer::clientDisconnected);
   // disconnect(klient,&QTcpSocket::errorOccurred,this,&TCPserwer::errorOccurred);
    /*qDebug()<<"To sie wykonuje 10";

    //serwer->close();
    qDebug()<<"To sie wykonuje 11";
    delete serwer;
    qDebug()<<"To sie wykonuje 12";
    serwer=nullptr;
    qDebug()<<"To sie wykonuje 13";
    //klient->close();
    qDebug()<<"To sie wykonuje 14";
    if(klient){
        klient->disconnectFromHost();
        if(klient->state()!=QAbstractSocket::UnconnectedState){
            klient->waitForDisconnected(1000);
        }
        klient->deleteLater();
        klient=nullptr;
    }
    _isStarted=false;
    */

    //WyslijWiadomoscDoKlienta(-1,0);
    //delete serwer;
   // serwer=nullptr;
    //delete klient;
   // klient=nullptr;
}
void TCPserwer::on_client_connecting(){
    qDebug()<<"Klient jest połączony z serwerem";
    klient = serwer->nextPendingConnection();

    connect(klient, &QTcpSocket::readyRead, this, &TCPserwer::OdbierzWiadomoscOdKlienta);
    connect(klient, &QTcpSocket::disconnected, this, &TCPserwer::clientDisconnected);
    connect(klient,&QTcpSocket::errorOccurred,this,&TCPserwer::errorOccurred);
    //klient->write("Siema na serwerze ziomal");
    qDebug() << "Emit newClient connected";
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
    //_isStarted = serwer->listen(QHostAddress::Any,numerPortu);
}

void TCPserwer::WyslijWiadomoscDoKlienta(int nrRamki,double warReg){
    //qDebug() << "Serwer próbuje wysłać ramkę:" << nrRamki << warReg;
    if (!klient) {
        qDebug() << "Brak klienta do wysyłki!";
        return;
    }

    QByteArray wiadomosc;
    QDataStream out(&wiadomosc, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_6);
    out << quint32(0) << nrRamki << warReg;
    out.device()->seek(0);
    out << quint32(wiadomosc.size() - sizeof(quint32));

    klient->write(wiadomosc);
    klient->flush();

    qDebug() << "Serwer wysłał ramkę:" << nrRamki << warReg;
}


void TCPserwer::OdbierzWiadomoscOdKlienta() {
    // 1. Dogadujemy się z QTcpSocket’em, że bierzemy wszystko, co przyszło
    bufor.append( klient->readAll() );

    const int headerSize = sizeof(quint32);
    // 2. Dopóki bufor ma przynajmniej miejsce na nagłówek…
    while (bufor.size() >= headerSize) {
        // 3. Odczytujemy długość payloadu
        QDataStream headerStream(bufor);
        headerStream.setVersion(QDataStream::Qt_6_6);

        quint32 msgSize = 0;
        headerStream >> msgSize;

        // 4. Jeżeli długość = 0 albo za duża – coś jest nie tak: usuń nagłówek i spróbuj dalej
        if (msgSize == 0 || msgSize > 1024) {
            qWarning() << "[SERWER] nieprawidłowy msgSize =" << msgSize
                       << "– usuwam tylko nagłówek, bufor był:" << bufor.size();
            bufor.remove(0, headerSize);
            continue;
        }

        // 5. Czekamy na cały payload
        if (bufor.size() < headerSize + int(msgSize)) {
            qDebug() << "[SERWER] czekam na pełną ramkę,"
                     << "potrzebuję" << (headerSize + msgSize)
                     << "mam" << bufor.size();
            break;
        }

        // 6. Wyciągamy payload do osobnego QByteArray (bez ryzyka „złe wskaźniki”)
        QByteArray payload = bufor.mid(headerSize, msgSize);
        QDataStream dataStream(&payload, QIODevice::ReadOnly);
        dataStream.setVersion(QDataStream::Qt_6_6);

        // 7. Deserializujemy
        int     nrRamki;
        quint8  stanSym;
        double  intCzas, wartSter;
        double warZad;
        dataStream >> nrRamki >> stanSym >> intCzas >> wartSter>>warZad;

        // 8. Debug i emit
        StanSymulacji s = static_cast<StanSymulacji>(stanSym);
        qDebug() << "[SERWER] odebrałem ramkę:"
                 << "nr=" << nrRamki
                 << "stan=" << int(s)
                 << "t="   << intCzas
                 << "u="   << wartSter;
        qDebug() << "Emit dane przetworzenia";
        emit daneDoPrzetworzenia(nrRamki, s, intCzas, wartSter,warZad);
        /*if(nrRamki==-1){
            nrRamki=0;
        }*/
        // 9. Usuwamy w całości (nagłówek + payload)
        bufor.remove(0, headerSize + msgSize);
        // pętla idzie dalej, jeśli jest coś jeszcze w buforze
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

    // 2) Jeśli serwer nasłuchuje – zamykamy gniazdo
    if (serwer->isListening()) {
        serwer->close();
    }
    _isStarted = false;
}
