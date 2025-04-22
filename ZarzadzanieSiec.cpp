#include "ZarzadzanieSiec.h"

ZarzadzanieSiec::ZarzadzanieSiec(QObject *parent)
    : QObject{parent}
{
    //connect(&socket, &QTcpSocket::readyRead, this, &ZarzadzanieSiec::OdbierzWiadomoscOdSerwera);
    connect(&socket,&QTcpSocket::connected,this,&ZarzadzanieSiec::connected);
    connect(&socket,&QTcpSocket::disconnected,this,&ZarzadzanieSiec::disconnected);
    connect(&socket,&QTcpSocket::stateChanged,this,&ZarzadzanieSiec::socketStateChanged);
    connect(&socket,&QTcpSocket::errorOccurred,this,&ZarzadzanieSiec::errorOccurred);
    //connect(&socket,&QTcpSocket::readyRead,this,&ZarzadzanieSiec::socket_readyRead);
    //connect(&socket, &QTcpSocket::readyRead, this, &ZarzadzanieSiec::OdbierzWiadomoscOdSerwera);

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
    //auto data =socket.readAll();
    //emit dataReady(data);
    OdbierzWiadomoscOdSerwera();
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
    //qDebug() << "Funkcja się odpaliła:";
    bufor.append(socket.readAll());

    QDataStream in(&bufor, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_6_8);

    while (true) {
        const int headerSize = sizeof(quint32);

        // Sprawdź, czy mamy wystarczająco danych, by odczytać długość wiadomości
        if (bufor.size() < headerSize) {
            //qDebug() << "Bufor zbyt mały na nagłówek – czekam na więcej danych.";
            return;
        }

        // Zapisz aktualną pozycję odczytu, żeby móc ją cofnąć w razie potrzeby
        in.device()->seek(0);

        // Odczytaj długość wiadomości
        quint32 dlugoscWiadomosci = 0;
        in >> dlugoscWiadomosci;

        //qDebug() << "Długość bufora: " << bufor.size();
       // qDebug() << "Nagłówek mówi, że wiadomość ma:" << dlugoscWiadomosci;
        //qDebug() << "Potrzeba co najmniej:" << headerSize + static_cast<int>(dlugoscWiadomosci);

        // Czy mamy już całą wiadomość?
        if (bufor.size() < headerSize + static_cast<int>(dlugoscWiadomosci)) {
            qDebug() << "Brakuje danych do pełnej wiadomości – czekam.";
            return;
        }

        // Odczytaj dane wiadomości
        int nrRamki;
        double wartoscReg;
        in >> nrRamki >> wartoscReg;

        //qDebug() << "Parsuję wiadomość:" << nrRamki << wartoscReg;
        emit daneSymulacji(nrRamki, wartoscReg);
        qDebug() << "Klient odebrał ramkę:" << nrRamki << wartoscReg;

        // Usuń przetworzoną wiadomość z bufora
        bufor.remove(0, headerSize + static_cast<int>(dlugoscWiadomosci));
    }
}

void ZarzadzanieSiec::UstawPolaczenia() {
    qDebug() << "ZarzadzanieSiec::UstawPolaczenia()";
    connect(&socket, &QTcpSocket::readyRead, this, &ZarzadzanieSiec::OdbierzWiadomoscOdSerwera);
}
void ZarzadzanieSiec::RozłączPolaczenia(){
    QAbstractSocket::disconnect(&socket, &QTcpSocket::readyRead, this, &ZarzadzanieSiec::OdbierzWiadomoscOdSerwera);
}
