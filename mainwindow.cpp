
#include "mainwindow.h"
#include <QApplication>
#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QtCharts/QChartView>
#include <QLineSeries>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QFont>
#include "mainwindow.h"
#include "Symulator.h"
#include <QMenu>
#include <QMetaEnum>
#include <QHostAddress>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent,Symulator *sym)
    : QMainWindow(parent),timer(new QTimer(this)),ui(new Ui::MainWindow)
{
    kopiaZadana=new QLineSeries();
    kopiaZadana->append(0,0);
    symulator = sym;
    symSiec = new Symulator();
    symWzorcowy = new Symulator();
    ui->setupUi(this);
    kopia = new Symulator(*symulator);
    //kopia=symulator;

    kopiaARX=new model_ARX(*symulator->get_arx());
    ui->layout_wykres1->setContentsMargins(0,0,0,0);
    ui->layout_wykres2->setContentsMargins(0,0,0,0);

    ui->layout_wykres1->setSpacing(0);
    ui->layout_wykres2->setSpacing(0);

    // definiuję, że każdy widget w layoutach ma „weight” = 1
    ui->layout_wykres1->setStretch(0, 1);
    ui->layout_wykres2->setStretch(0, 1);
    ui->layout_wykres2->setStretch(1, 1);
    ustawienieWykresow();
    ui->arxA_Input->setText("-0.4;");
    ui->arxB_Input->setText("0.6;");
    ui->opoznienie_Input->setText("1");

    ui->PIDwzmocnienie_Input->setText("0.1");
    ui->PIDTi_input->setText("5");
    ui->PIDTd_input->setText("0.1");

    ui->GenAmp_input->setText("1");
    ui->GenT_Input->setText("10");
    ui->GenFill_Input->setText("0.5");
    ui->interwal_Input->setText("0.043");
    ui->zaklocenia_Input->setText("0");

    timer->setInterval(34);

    if(symulator->get_pid()->get_tryb_I())
    {
            ui->Tryb_label->setText("Pod całką");
    }
    else
    {
            ui->Tryb_label->setText("Przed całką");
    }
    ui->save_button->setVisible(false);
    ui->load_button->setVisible(false);
    ui->arxA_Input->setVisible(false);
    ui->arxB_Input->setVisible(false);
    ui->opoznienie_Input->setVisible(false);
    ui->zaklocenia_Input->setVisible(false);
    ustawienieWartosci();


    //Sieć i nasze zmiany
    serwer = nullptr;
    serwerWlaczony=false;
    menu = new QMenu(this);
    menu->addAction("Serwer");
    menu->addAction("Klient");
    menu->setFixedWidth(ui->WyborRoli->width());
    ui->WyborRoli->setMenu(menu);
    ui->WyborRoli->setPopupMode(QToolButton::InstantPopup);

    //ui->Przesylanie->setEnabled(false);
    ui->WyborRoli->setEnabled(false);
    ui->btnWlacz->setEnabled(false);
    ui->btnWylacz->setEnabled(false);
    //ui->btnWyslij->setEnabled(false);
    //ui->DanePrzeslij->setEnabled(false);
    ui->DaneDoPolaczenia->setEnabled(false);
    ui->statusPolaczony->setStyleSheet("QLabel { color: rgb(160, 160, 160); }");
    connect(timer,SIGNAL(timeout()),this,SLOT(simulationProgress()));//connect do standardowej symulacji
    adres="127.0.0.1";
    port=12345;
    //Sieć Klient

    klientPołączony=false;
    serwerPołączony=false;

    danePobierane = new DanePobierane(this);

    SerwerJuzWystartowal=false;
    numerRamki=0;
    //connect(timer,&QTimer::timeout,this,&MainWindow::WysylanieRamki);
    connect(&siec,&ZarzadzanieSiec::daneSymulacji,this,&MainWindow::DaneSymulacjiOdSerwera);
    connect(serwer,&TCPserwer::daneDoPrzetworzenia,this,&MainWindow::ObliczeniaObiektu);


    connect(this, &MainWindow::wracamyTrybSieciowy, this, &MainWindow::on_trybSieciowy_clicked);

    connect(timer,SIGNAL(timeout()),this,SLOT(simulationProgress()));//connect do standardowej symulacji
    connect(serwer,&TCPserwer::errorOccurred,this,&MainWindow::siec_errorOccurred);
    connect(danePobierane,&DanePobierane::PrzesylanieDanych,this,&MainWindow::PrzypisanieAdresuIportu);
    connect(danePobierane,&DanePobierane::BledneDane,this,&MainWindow::BledneDane);
}
void MainWindow::on_reset_button_clicked()
{
    timer->stop();
    symulator->set_arx({0} ,{0},1,0);
    symulator->set_pid(0,0,0);
    symulator->set_gen(0,0,0);
    st=StanSymulacji::Reset;
    chartPos = 0;
    chartPos_zero = 0;
    chartX = 100;
    chartY=1.0;
    chart->axes(Qt::Horizontal).first()->setRange(chartPos_zero,chartX);

    chart1->axes(Qt::Horizontal).first()->setRange(chartPos_zero,chartX);
    chart2->axes(Qt::Horizontal).first()->setRange(chartPos_zero,chartX);

    chart->axes(Qt::Vertical).first()->setRange(-chartY,chartY);

    chart1->axes(Qt::Vertical).first()->setRange(-chartY,chartY);


    chart2->axes(Qt::Vertical).first()->setRange(-chartY,chartY);

    chart_Zadany_scale = 1;
    chart_PID_scale = 1;
    chart_Uchyb_scale = 1;

    chart_Zadany_scale_below = -1;
    chart_PID_scale_below = -1;
    chart_Uchyb_scale_below = -1;

    symulator->get_pid()->reset_Derivative();
    symulator->get_pid()->reset_Intergral();
    symulator->get_arx()->reset();
    symulator->reset();

    seriesZ->clear();
    seriesU->clear();
    seriesSterowanie->clear();
    seriesI->clear();
    seriesD->clear();

    seriesP->clear();
    seriesR->clear();

    chart->update();
    chart1->update();

    chart2->update();

    ui->start_button->setEnabled(1);
    ui->save_button->setEnabled(1);
    ui->load_button->setEnabled(1);
    wartoscSterujaca=0;
    wartoscReg=0;
    wartoscZadana=0;
    numerRamki=0;
    intCzas=0;
    if(siec.isConnected()){
        siec.WyslijWiadomoscDoSerwera(numerRamki, st, intCzas, wartoscSterujaca,wartoscZadana);

    }

}
MainWindow::~MainWindow()
{
    siec.disconnect();
    delete serwer;
    serwer=nullptr;
}

void MainWindow::on_start_button_clicked()
{
    if(st==StanSymulacji::Reset){
        ustawienieWartosci();
    }
    st=StanSymulacji::Start;

    ui->start_button->setEnabled(0);
    ui->save_button->setEnabled(0);
    ui->load_button->setEnabled(0);
    if(czyTrybSieciowy)
    {
        if(wybor=="Klient" || wybor=="Serwer")
        {
            if(siec.isConnected()){
               timer->start();
            }else{
                QMessageBox::warning(this,"Błąd","Brak Połączenia");
                ui->start_button->setEnabled(true);
            }

        }else{
            QMessageBox::warning(this,"Błąd","Nie wybrałeś roli");
        }
    }else
    {
        timer->start();

    }

}
void MainWindow::wczytaj_dane_okno()
{
    std::vector<double> arxA_val = {};
    arxA_val = dane.wektor_A;

    std::vector<double> arxB_val = {};
    arxB_val = dane.wektor_B;

    int opoznienie = 1;
    opoznienie = dane.opoznienie;

    double disturbance_amp = 0.0;
    disturbance_amp = dane.blad;

    symulator->set_arx(arxA_val,
                       arxB_val,
                       opoznienie,
                       disturbance_amp);
    arx->set_Wszystko(arxA_val,
                       arxB_val,
                       opoznienie,
                       disturbance_amp);
}
void MainWindow::simulationProgress()
{
    if(chartPos > chartX) chartX++;
    chart->axes(Qt::Horizontal).first()->setRange(chartPos_zero+1,chartX);
    chart1->axes(Qt::Horizontal).first()->setRange(chartPos_zero+1,chartX);
    chart2->axes(Qt::Horizontal).first()->setRange(chartPos_zero+1,chartX);

    if(czyTrybSieciowy){
        if(wybor == "Klient"||wybor=="Serwer"){//{wybor=="Serwer"||
        wartoscSterujaca=symulator->SymulacjaGeneratorRegulator();
        symulator->AktualizacjaObiektu(wartoscReg);
        if(siec.isConnected()&&wybor=="Klient"){
            wartoscZadana=symulator->get_gen_val();
           WysylanieRamki();
        }

        }
    }else{
        qDebug()<<"Symuluje";
      symulator->simulate();
    }


    if(wybor=="Serwer"){
        seriesR->append(chartPos,wartoscReg);
        seriesZ->append(chartPos,wartoscZadana);
        seriesSterowanie->append(chartPos,wartoscRegulatora);
    }
    else{
        seriesR->append(chartPos,symulator->get_arx_val());
        seriesZ->append(chartPos,symulator->get_gen_val());
        seriesSterowanie->append(chartPos,symulator->get_pid_val());
    }

    seriesU->append(chartPos,symulator->get_pid()->get_diff());
    seriesP->append(chartPos,symulator->get_pid()->get_p_out());
    seriesI->append(chartPos,symulator->get_pid()->get_i_out());
    seriesD->append(chartPos,symulator->get_pid()->get_d_out());

    chartPos++;

    if(chartPos >= 100)
    {
        chartPos_zero++;
        seriesR->remove(0);
        seriesZ->remove(0);
        seriesU->remove(0);
        seriesP->remove(0);
        seriesI->remove(0);
        seriesD->remove(0);
        seriesSterowanie->remove(0);

    }
    if(chartPos % 10 == 0)
    {
        val_chart_1 = 0.0;
        val_chart_2 = 0.0;
        val_chart_3 = 0.0;
        val_chart_4 =0.0;
        val_chart_1_min = 0.0;
        val_chart_2_min = 0.0;
        val_chart_3_min = 0.0;
        val_chart_4_min =0.0;
        chart_Zadany_scale = 0.01;
        chart_Zadany_scale_below = -0.01;
        chart_Uchyb_scale = 0.01;
        chart_Uchyb_scale_below = -0.01;
        chart_PID_scale = 0.01;
        chart_PID_scale_below = -0.01;
    }
    foreach (QPointF val_R, seriesR->points())
    {
        if(val_chart_1 < val_R.y()) val_chart_1=val_R.y();
        if(val_chart_1_min > val_R.y()) val_chart_1_min=val_R.y();
    }

    foreach (QPointF val_Z, seriesZ->points())
    {
        if(val_chart_1 < val_Z.y()) val_chart_1=val_Z.y();
        if(val_chart_1_min > val_Z.y()) val_chart_1_min=val_Z.y();
    }
    foreach (QPointF val_U, seriesU->points())
    {
        if(val_chart_2 < val_U.y()) val_chart_2=val_U.y();
        if(val_chart_2_min > val_U.y()) val_chart_2_min=val_U.y();
    }
    foreach (QPointF val_P, seriesP->points())
    {
        if(val_chart_3 < val_P.y()) val_chart_3=val_P.y();
        if(val_chart_3_min > val_P.y()) val_chart_3_min=val_P.y();
    }
    foreach (QPointF val_I, seriesI->points())
    {
        if(val_chart_3 < val_I.y()) val_chart_3=val_I.y();
         if(val_chart_3_min > val_I.y()) val_chart_3_min=val_I.y();
    }
    foreach (QPointF val_D, seriesD->points())
    {
        if(val_chart_3 < val_D.y()) val_chart_3=val_D.y();
         if(val_chart_3_min > val_D.y()) val_chart_3_min=val_D.y();
    }
    if(wybor=="Serwer"){
        foreach (QPointF val_S, seriesSterowanie->points())
        {
            if(val_chart_4 < val_S.y()) val_chart_4=val_S.y();
            if(val_chart_4_min > val_S.y()) val_chart_4_min=val_S.y();
        }
    }
    chart_Zadany_scale =val_chart_1 * 1.1;
    chart_Zadany_scale_below = val_chart_1_min * 1.1;
    if(val_chart_2 > 0.01)
    {
    chart_Uchyb_scale = val_chart_2 * 1.1;
    }
    if(val_chart_2_min < -0.01)
    {
    chart_Uchyb_scale_below = val_chart_2_min * 1.1;
    }
    if(wybor=="Serwer"){
        chart_PID_scale = val_chart_4 * 1.1;
        chart_PID_scale_below = val_chart_4_min * 1.1;
    }else{
        chart_PID_scale = val_chart_3 * 1.1;
        chart_PID_scale_below = val_chart_3_min * 1.1;
    }
    chart->axes(Qt::Vertical).first()->setRange(chart_Zadany_scale_below,chart_Zadany_scale);
    chart1->axes(Qt::Vertical).first()->setRange(chart_Uchyb_scale_below,chart_Uchyb_scale);
    chart2->axes(Qt::Vertical).first()->setRange(chart_PID_scale_below,chart_PID_scale);

    chart->update();
    chart1->update();
    chart2->update();

}
void MainWindow::on_stop_button_clicked()
{
    if(siec.isConnected()){
        siec.WyslijWiadomoscDoSerwera(-1,StanSymulacji::Stop,0,0,0);

    }
    st=StanSymulacji::Stop;
    timer->stop();
    ui->start_button->setEnabled(1);
    ui->save_button->setEnabled(1);
    ui->load_button->setEnabled(1);

}
void MainWindow::on_PIDwzmocnienie_Input_editingFinished()
{
    if(!ui->PIDwzmocnienie_Input->text().isEmpty())
    {
        symulator->get_pid()->set_k(ui->PIDwzmocnienie_Input->text().toDouble());
    }
}
void MainWindow::on_PIDTi_input_editingFinished()
{
    if(!ui->PIDTi_input->text().isEmpty())
    {
        symulator->get_pid()->set_Ti(ui->PIDTi_input->text().toDouble());
    }
}

void MainWindow::on_PIDTd_input_editingFinished()
{
    if(!ui->PIDTd_input->text().isEmpty())
    {
        symulator->get_pid()->set_Td(ui->PIDTd_input->text().toDouble());
    }
}


void MainWindow::on_GenAmp_input_editingFinished()
{
    if(!ui->GenAmp_input->text().isEmpty())
    {
        symulator->get_gen()->set_Amp(ui->GenAmp_input->text().toDouble());
    }
}


void MainWindow::on_GenT_Input_editingFinished()
{
    if(!ui->GenT_Input->text().isEmpty())
    {
        symulator->get_gen()->set_T(ui->GenT_Input->text().toInt());
    }
}


void MainWindow::on_GenFill_Input_editingFinished()
{
    if(!ui->GenFill_Input->text().isEmpty())
    {
        symulator->get_gen()->set_fill(ui->GenFill_Input->text().toDouble());
    }
}


void MainWindow::on_genType_Box_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    switch (ui->genType_Box->currentIndex()) {
    case 0:
        symulator->set_generator_type(typ_generatora::gen_Skok);
        break;
    case 1:
        symulator->set_generator_type(typ_generatora::gen_Sin);
        break;
    case 2:
        symulator->set_generator_type(typ_generatora::gen_Syg);
        break;
    default:
        symulator->set_generator_type(typ_generatora::gen_Skok);
        break;
    }
}


void MainWindow::on_interwal_Input_editingFinished()
{
    if(!ui->interwal_Input->text().isEmpty())
    {
        timer->setInterval(ui->interwal_Input->text().toDouble()*1000);
    }
}

void MainWindow::on_Tryb_I_toggled(bool checked)
{
    if(checked)
    {
        symulator->get_pid()->set_tryb_I(true);
        ui->Tryb_label->setText("Pod całką");
    }
    else
    {
        symulator->get_pid()->set_tryb_I(false);
        ui->Tryb_label->setText("Przed całką");
    }
}


void MainWindow::on_PID_reset_I_clicked()
{
    symulator->get_pid()->reset_Intergral();
}


void MainWindow::on_Arx_window_btn_clicked()
{
    okno = new ARX_window(dane,this);
    okno->show();

}


void MainWindow::on_btnWlacz_clicked()
{

    if(wybor=="Serwer"){
        if(port>0){
            if(serwer==nullptr)
            {   if(!klikniete){
                serwer = new TCPserwer(this,port);
                }

                connect(serwer, &TCPserwer::newClientConnected, this, &MainWindow::on_NewClientConnected);
                //connect(serwer, &TCPserwer::dataReceived, this, &MainWindow::clientDataReceived);
                connect(serwer, &TCPserwer::clientDisconnect, this, &MainWindow::clientDisconnected);
                disconnect(&siec,&ZarzadzanieSiec::daneSymulacji,this,&MainWindow::DaneSymulacjiOdSerwera);
                connect(serwer,&TCPserwer::daneDoPrzetworzenia,this,&MainWindow::ObliczeniaObiektu);
                connect(serwer,&TCPserwer::errorOccurred,this,&MainWindow::siec_errorOccurred);
                siec.RozłączPolaczenia();

            }
        }
        else if(wybor!="Serwer"&&wybor!="Klient"){
            QMessageBox::warning(this,"Błąd","Nie wybrałeś portu");
        }

    }else if(wybor=="Klient"){
            setZarzadzanieSiec();
            connect(&siec,&ZarzadzanieSiec::daneSymulacji,this,&MainWindow::DaneSymulacjiOdSerwera);
            disconnect(serwer,&TCPserwer::daneDoPrzetworzenia,this,&MainWindow::ObliczeniaObiektu);
            siec.UstawPolaczenia();
            siec.connectToDevice(adres,port);

    }

}
void MainWindow::on_btnWylacz_clicked()
{
    QMessageBox::StandardButton potwierdzenie;
    if(wybor=="Klient"){
        if(siec.isConnected()){
            potwierdzenie = QMessageBox::question(this, "Potwierdzenie", "Czy na pewno chcesz rozłączyć klienta?",
            QMessageBox::Yes | QMessageBox::No);
            if (potwierdzenie == QMessageBox::Yes){
                poprawneWylaczenie=true;
                siec.WyslijWiadomoscDoSerwera(-1,StanSymulacji::Stop,0,0,0);
                disconnect(&siec,nullptr,this,nullptr);
                siec.disconnect();
                timer->stop();
                ui->start_button->setEnabled(true);
            }

        }

    }else if(wybor=="Serwer"){
        if(serwer!=nullptr){
            potwierdzenie = QMessageBox::question(this, "Potwierdzenie", "Czy na pewno chcesz wyłączyć serwer?",
            QMessageBox::Yes | QMessageBox::No);
            if (potwierdzenie == QMessageBox::Yes){
                //QMessageBox::information(this,"Info","Rozłączono Połączenie");
                ui->wyswietlanyPort->setText("");

            ui->statusPolaczony->setText("Niepołączony");
            ui->statusPolaczony->setStyleSheet("QLabel { color : red; }");
            poprawneWylaczenie=true;
            serwer->WyslijWiadomoscDoKlienta(-1,0);
            delete serwer;
            serwer=nullptr;}
        }
        klikniete=false;
    }


}
void MainWindow::on_NewClientConnected()
{
    //serwer->setNrRamki();
    poprawneWylaczenie=false;
    klientPołączony=true;
    ui->statusPolaczony->setText("Połączony");
    ui->statusPolaczony->setStyleSheet("QLabel { color : green; }");
    QString adresKl;
    quint16 portKl;
    serwer->AdresIport(adresKl,portKl);
    ui->wyswietlanyAdres->setText(adresKl);
    ui->wyswietlanyPort->setText(QString::number(portKl));
    qDebug() << "Klient się połączył";
}

void MainWindow::clientDisconnected(){

    if(!poprawneWylaczenie){

        ui->trybSieciowy->setCheckState(Qt::Unchecked);
        emit wracamyTrybSieciowy(false);
        QMessageBox::information(this,"Info","Rozłączono Połączenie");
    }

    qDebug()<<"Klient rozłączony";
    klientPołączony=false;
    ui->wyswietlanyAdres->setText("");
    ui->wyswietlanyPort->setText("");
    ui->statusPolaczony->setText("Niepołączony");
    ui->statusPolaczony->setStyleSheet("QLabel { color : red; }");
}
void MainWindow::on_WyborRoli_clicked()
{
    ui->WyborRoli->showMenu();
}


void MainWindow::on_WyborRoli_triggered(QAction *arg1)
{
    wybor = arg1->text();
    if(wybor=="Serwer"){
        //usuniecieWykresow();
        //ustawienieWykresowSerwer();
        ustawienieWykresowSerwer();
        if(siec.isConnected()){
            siec.disconnect();
        }
        ui->btnWlacz->setText("Włącz");
        ui->btnWylacz->setText("Wyłącz");
        ui->WyborRoli->setText("Serwer");


        ui->box_pid->setEnabled(false);
        ui->box_add->setEnabled(false);
        ui->box_gen->setEnabled(false);
        ui->box_arx->setEnabled(true);
        ui->Tryb_label->setEnabled(false);

        ui->start_button->setEnabled(false);
        ui->reset_button->setEnabled(false);
        ui->Tryb_I->setEnabled(false);
        ui->PID_reset_I->setEnabled(false);
        ui->stop_button->setEnabled(false);

    }else if(wybor=="Klient"){
        if(wykresSchowany){
            ponowneUstawienieWykresow();
        }
        if(serwer!=nullptr){
            delete serwer;
            serwer=nullptr;
        }
        ui->btnWlacz->setText("Połącz");
        ui->btnWylacz->setText("Rozłącz");
        ui->WyborRoli->setText("Klient");


        ui->box_arx->setEnabled(false);
        ui->box_pid->setEnabled(true);
        ui->box_add->setEnabled(true);
        ui->box_gen->setEnabled(true);

        ui->start_button->setEnabled(true);
        ui->reset_button->setEnabled(true);
        ui->Tryb_I->setEnabled(true);
        ui->PID_reset_I->setEnabled(true);
        ui->stop_button->setEnabled(true);

    }

    ui->statusPolaczony->setText("Niepołączony");
    ui->statusPolaczony->setStyleSheet("QLabel { color : red; }");
    danePobierane->UstawienieDostepnosci(wybor);
}


//Sieć metody i sloty dla klienta

void MainWindow::setZarzadzanieSiec(){
    qDebug() << "MainWindow konstruktor start";
    connect(&siec,&ZarzadzanieSiec::connected,this,&MainWindow::siec_connected);
    connect(&siec,&ZarzadzanieSiec::disconnected,this,&MainWindow::siec_disconnected);
    connect(&siec,&ZarzadzanieSiec::stateChanged,this,&MainWindow::siec_stateChanged);
    connect(&siec,&ZarzadzanieSiec::errorOccurred,this,&MainWindow::siec_errorOccurred);
    qDebug() << "setZarzadzanieSiec wywołane";
    siec.UstawPolaczenia();
    qDebug() << "MainWindow konstruktor koniec";
}


void MainWindow::siec_connected(){

    poprawneWylaczenie=false;
    qDebug("Podłączono");
    serwerPołączony=true;
    ui->statusPolaczony->setText("Połączony");
    ui->statusPolaczony->setStyleSheet("QLabel { color : green; }");
    ui->wyswietlanyAdres->setText(adres);
    ui->wyswietlanyPort->setText(QString::number(port));
}
void MainWindow::siec_disconnected(){

    if(!poprawneWylaczenie){
        ui->trybSieciowy->setCheckState(Qt::Unchecked);
        emit wracamyTrybSieciowy(false);
        QMessageBox::information(this,"Info","Rozłączono Połączenie");
    }
    qDebug("Rozłączono");
    serwerPołączony=false;
    ui->wyswietlanyAdres->setText("");
    ui->wyswietlanyPort->setText("");
    ui->statusPolaczony->setText("Niepołączony");
    ui->statusPolaczony->setStyleSheet("QLabel { color : red; }");

}
void MainWindow::siec_stateChanged(QAbstractSocket::SocketState state){

    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    qDebug() << metaEnum.valueToKey(state);
}
void MainWindow::siec_errorOccurred(QAbstractSocket::SocketError error){
    Q_UNUSED(error);
    if(!poprawneWylaczenie){

        ui->trybSieciowy->setCheckState(Qt::Unchecked);
        emit wracamyTrybSieciowy(false);
        QMessageBox::information(this,"Info","Rozłączono Połączenie");
    }


}


void MainWindow::on_DaneDoPolaczenia_clicked()
{
    danePobierane->exec();
}

void MainWindow::PrzypisanieAdresuIportu(QString a,quint16 p){
    adres=a;
    port=p;
    if(serwer!=nullptr){
        delete serwer;
        serwer = new TCPserwer(this,port);

    }
}
void MainWindow::BledneDane(){
    QMessageBox::warning(this,"Błąd","Błedne Dane");
}

void MainWindow::WysylanieRamki(){
    qDebug() << "To sie wykonuje - wysylanie ramki";
    if(siec.isConnected()){
      siec.WyslijWiadomoscDoSerwera(++numerRamki, st, intCzas, wartoscSterujaca,wartoscZadana);

    }

}

void MainWindow::DaneSymulacjiOdSerwera(int n,double w){
    if(n==-1){
        ui->start_button->setEnabled(true);
        if(siec.isConnected()){
            siec.setNrRamki();
            numerRamki=0;
        }

    }
    if(n==numerRamki){
        ui->LEDdioda->setStyleSheet("QLabel { background-color: green; color: white; }");
    }else{
        ui->LEDdioda->setStyleSheet("QLabel { background-color: red; color: white; }");
    wartoscReg=w;
    qDebug() << "MainWindow odebrał ramkę od serwera:" << n << w;
    }}

void MainWindow::ObliczeniaObiektu(int nrRam,StanSymulacji s,double i, double w,double wZ){
    if(nrRam==-1){
        poprawneWylaczenie=true;
        numerRamki=0;
        if(serwer!=nullptr){
            serwer->setNrRamki();
        }

    }
    st=s;
    if(nrRam==numerRamki+1){
        ui->LEDdioda->setStyleSheet("QLabel { background-color: green; color: white; }");
    }else{
        ui->LEDdioda->setStyleSheet("QLabel { background-color: red; color: white; }");
    }
    numerRamki=nrRam;
    //wartoscReg=w;
   // qDebug() << "MainWindow::ObliczeniaObiektu wywołane!";
    if (!arx) {
        arx = new model_ARX(dane.wektor_A, dane.wektor_B, dane.opoznienie, dane.blad); // lub użyj jakiejś konfiguracji domyślnej albo przekazywanej
    }
    if(arx->getZresetowany()==true){
        arx->set_Wszystko(dane.wektor_A, dane.wektor_B, dane.opoznienie, dane.blad);
        arx->setZresetowany(false);
    }
    if(s==StanSymulacji::Start){
        //timerSerwer->start();

        wartoscReg=arx->Simulate(w);
        wartoscRegulatora=w;
        wartoscZadana=wZ;
        //symulacjaSerwer(wartoscReg,w,wZ);
        simulationProgress();
        numerRamki=nrRam;
    }else if(s==StanSymulacji::Reset){
        //timerSerwer->stop();
        arx->set_Wszystko({0} ,{0},1,0);
        arx->reset();
        arx->setZresetowany(true);
        on_reset_button_clicked();
        ustawienieWykresowSerwer();
        wartoscReg=0;
        numerRamki=0;
\
    }
    else{
        //timerSerwer->stop();
        //nic nie robimy, ale jeszcze do przemyslenia
    }
    if(serwer!=nullptr){
       serwer->WyslijWiadomoscDoKlienta(numerRamki,wartoscReg);
    }

}

void MainWindow::setDaneSymulatora(){

    symulator->set_arx(dane.wektor_A,
                       dane.wektor_B,
                       dane.opoznienie,
                       dane.blad);
    if(!ui->PIDwzmocnienie_Input->text().isEmpty() || !ui->PIDTi_input->text().isEmpty()|| !ui->PIDTd_input->text().isEmpty())
    {
        symulator->set_pid(ui->PIDwzmocnienie_Input->text().toDouble()
                           ,ui->PIDTi_input->text().toDouble()
                           ,ui->PIDTd_input->text().toDouble());
    }

    if(!ui->GenAmp_input->text().isEmpty() || !ui->GenT_Input->text().isEmpty() || !ui->GenFill_Input->text().isEmpty())
    {
        symulator->set_gen(ui->GenAmp_input->text().toDouble()
                           ,ui->GenT_Input->text().toInt()
                           ,ui->GenFill_Input->text().toDouble());
    }

    //
    switch (ui->genType_Box->currentIndex()) {
    case 0:
        symulator->set_generator_type(typ_generatora::gen_Skok);
        break;
    case 1:
        symulator->set_generator_type(typ_generatora::gen_Sin);
        break;
    case 2:
        symulator->set_generator_type(typ_generatora::gen_Syg);
        break;
    default:
        symulator->set_generator_type(typ_generatora::gen_Skok);
        break;
    }
    if(!ui->interwal_Input->text().isEmpty())
    {
        timer->setInterval(ui->interwal_Input->text().toDouble()*1000);
    }
}


void MainWindow::ustawienieWartosci(){
    std::vector<double> arxA_val = {};
    arxA_val = dane.wektor_A;

    std::vector<double> arxB_val = {};
    arxB_val = dane.wektor_B;

    int opoznienie = 1;
    opoznienie = dane.opoznienie;

    double disturbance_amp = 0.0;
    disturbance_amp = dane.blad;

    symulator->set_arx(arxA_val,
                       arxB_val,
                       opoznienie,
                       disturbance_amp);
    if(!ui->PIDwzmocnienie_Input->text().isEmpty() || !ui->PIDTi_input->text().isEmpty()|| !ui->PIDTd_input->text().isEmpty())
    {
        symulator->set_pid(ui->PIDwzmocnienie_Input->text().toDouble()
                           ,ui->PIDTi_input->text().toDouble()
                           ,ui->PIDTd_input->text().toDouble());
    }

    if(!ui->GenAmp_input->text().isEmpty() || !ui->GenT_Input->text().isEmpty() || !ui->GenFill_Input->text().isEmpty())
    {
        symulator->set_gen(ui->GenAmp_input->text().toDouble()
                           ,ui->GenT_Input->text().toInt()
                           ,ui->GenFill_Input->text().toDouble());
    }

    //
    switch (ui->genType_Box->currentIndex()) {
    case 0:
        symulator->set_generator_type(typ_generatora::gen_Skok);
        break;
    case 1:
        symulator->set_generator_type(typ_generatora::gen_Sin);
        break;
    case 2:
        symulator->set_generator_type(typ_generatora::gen_Syg);
        break;
    default:
        symulator->set_generator_type(typ_generatora::gen_Skok);
        break;
    }
    if(!ui->interwal_Input->text().isEmpty())
    {
        timer->setInterval(ui->interwal_Input->text().toDouble()*1000);
    }
}

void MainWindow::ustawieniePonowneARX(){

    std::vector<double> arxA_val = {};
    arxA_val = dane.wektor_A;

    std::vector<double> arxB_val = {};
    arxB_val = dane.wektor_B;

    int opoznienie = 1;
    opoznienie = dane.opoznienie;

    double disturbance_amp = 0.0;
    disturbance_amp = dane.blad;

    symulator->set_arx(arxA_val,
                       arxB_val,
                       opoznienie,
                       disturbance_amp);

}

void MainWindow::on_trybSieciowy_clicked(bool checked)
{
    czyTrybSieciowy = checked;
    if(czyTrybSieciowy==true){
        poprawneWylaczenie=false;
        timer->stop();
        st=StanSymulacji::Reset;
        on_reset_button_clicked();
        ui->WyborRoli->setEnabled(true);
        ui->btnWlacz->setEnabled(true);
        ui->DaneDoPolaczenia->setEnabled(true);
        ui->statusPolaczony->setStyleSheet("QLabel { color : red; }");
        klikniete=false;
        ui->btnWylacz->setEnabled(true);

    }else if(czyTrybSieciowy==false){
        if(wybor=="Klient"){
            if(siec.isConnected()){
                qDebug() << "To sie wykonuje - tryb sieciowy clicked";
                siec.WyslijWiadomoscDoSerwera(-1,StanSymulacji::Stop,0,0,0);

                disconnect(&siec,nullptr,this,nullptr);
                siec.RozłączPolaczenia();

                siec.disconnect();
            }
        }

        if(wykresSchowany){
            ponowneUstawienieWykresow();
        }
        poprawneWylaczenie=true;
        ustawieniePonowneARX();
        ui->wyswietlanyAdres->setText("");
        ui->wyswietlanyPort->setText("");
        ui->WyborRoli->setEnabled(false);
        ui->WyborRoli->setText("Wybierz");
        ui->btnWlacz->setEnabled(false);
        ui->btnWylacz->setEnabled(false);
        ui->btnWlacz->setText("Włącz");
        ui->btnWylacz->setText("Wyłącz");
        danePobierane->Czyszczenie();
        ui->DaneDoPolaczenia->setEnabled(false);
        klientPołączony=false;
        serwerPołączony=false;
        ui->statusPolaczony->setText("Niepołączony");
        ui->statusPolaczony->setStyleSheet("QLabel { color: rgb(160, 160, 160); }");

        if(wybor=="Serwer"){

            symulator->setARX(*arx);
            if(!ui->PIDwzmocnienie_Input->text().isEmpty() || !ui->PIDTi_input->text().isEmpty()|| !ui->PIDTd_input->text().isEmpty())
            {
                symulator->set_pid(ui->PIDwzmocnienie_Input->text().toDouble()
                                   ,ui->PIDTi_input->text().toDouble()
                                   ,ui->PIDTd_input->text().toDouble());
            }
            if(!ui->GenAmp_input->text().isEmpty() || !ui->GenT_Input->text().isEmpty() || !ui->GenFill_Input->text().isEmpty())
            {
                symulator->set_gen(ui->GenAmp_input->text().toDouble()
                                   ,ui->GenT_Input->text().toInt()
                                   ,ui->GenFill_Input->text().toDouble());
            }
            switch (ui->genType_Box->currentIndex()) {
            case 0:
                symulator->set_generator_type(typ_generatora::gen_Skok);
                break;
            case 1:
                symulator->set_generator_type(typ_generatora::gen_Sin);
                break;
            case 2:
                symulator->set_generator_type(typ_generatora::gen_Syg);
                break;
            default:
                symulator->set_generator_type(typ_generatora::gen_Skok);
                break;
            }
            if(!ui->interwal_Input->text().isEmpty())
            {
                timer->setInterval(ui->interwal_Input->text().toDouble()*1000);
            }
            qDebug()<<"To sie wykonuje 7";
            if(st==StanSymulacji::Start){
             timer->start();
            }
            qDebug()<<"To sie wykonuje 8";

        }
        if(ui->start_button->isEnabled()||wybor=="Serwer"){
            ui->start_button->setEnabled(true);
        }
        wybor="Nikt";
        danePobierane->UstawienieDostepnosci(wybor);
        danePobierane->Czyszczenie();

        ui->box_pid->setEnabled(true);
        ui->box_add->setEnabled(true);
        ui->box_gen->setEnabled(true);
        SerwerJuzWystartowal=false;
        klikniete=false;
        ui->box_arx->setEnabled(true);
        ui->reset_button->setEnabled(true);
        ui->Tryb_I->setEnabled(true);
        ui->PID_reset_I->setEnabled(true);
        ui->stop_button->setEnabled(true);
    }
    if(serwer!=nullptr){
        //disconnect(serwer,nullptr,this,nullptr);
       // delete serwer;
        serwer->close();

        // ponowne uruchomienie nasłuchu
        bool ok = serwer->sprawdzenieSerwera(port);  // po poprawieniu tej metody tak, by korzystała z serwer->listen()
        if (!ok) {
            //qDebug() << "Nie udało się wznowić nasłuchiwania: " << numerPortu;
        qDebug()<<"To sie wykonuje 4";
        //serwer=nullptr;
        }
    }
}

void MainWindow::ustawienieWykresow(){
    ui->layout_wykres1->setStretch(0,1);
    ui->layout_wykres2->setStretch(0,1);
    ui->layout_wykres2->setStretch(1,1);
    QFont font;
    font.setPointSize(8);
    seriesZ = new QLineSeries();
    seriesZ->setName("Wartość zadana");
    seriesZ->append(0,0);
    seriesR = new QLineSeries();
    seriesR->setName("Wartość regulowana");
    seriesR->append(0,0);

    chart = new QChart();
    chart->setTitle("Wykres wartości zadanej i regulowanej");
    chart->legend()->setVisible(true);
    chart->addSeries(seriesZ);
    chart->addSeries(seriesR);
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0,chartX);
    chart->axes(Qt::Vertical).first()->setRange(-chartY,chartY);
    chart->setVisible(true);
    chart->axes(Qt::Horizontal).first()->setTitleText("Czas");
    chart->axes(Qt::Vertical).first()->setTitleText("Wartość");
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(300,200);
    chartView->setMaximumSize(1500,900);

    seriesP = new QLineSeries();
    seriesP->setName("Część proporcjonalna");
    //Wykres części całkującej sterowania
    seriesI = new QLineSeries();
    seriesI->setName("Część całkująca");
    //Wykres części całkującej sterowania
    seriesD = new QLineSeries();
    seriesD->setName("Część różniczkująca");
    seriesSterowanie = new QLineSeries();
    seriesSterowanie->setName("Wartość sterująca");
    chart2 = new QChart();
    chart2->setTitle("Wykres PID");
    chart2->legend()->setVisible(true);
    chart2->addSeries(seriesP);
    chart2->addSeries(seriesI);
    chart2->addSeries(seriesD);
    chart2->addSeries(seriesSterowanie);
    seriesSterowanie->hide();
    chart2->createDefaultAxes();
    chart2->axes(Qt::Horizontal).first()->setRange(0,chartX);
    chart2->axes(Qt::Vertical).first()->setRange(-chartY,chartY);
    chart2->axes(Qt::Horizontal).first()->setTitleText("Czas");
    chart2->axes(Qt::Vertical).first()->setTitleText("Wartość");
    chartView2 = new QChartView(chart2);
    chartView2->setRenderHint(QPainter::Antialiasing);
    chartView2->setMinimumSize(300,200);
    chartView2->setMaximumSize(1500,400);

    seriesU = new QLineSeries();
    seriesU->setName("Uchyb");
    chart1 = new QChart();
    chart1->setTitle("Wykres uchybu");
    chart1->legend()->setVisible(true);
    chart1->addSeries(seriesU);
    chart1->createDefaultAxes();
    chart1->axes(Qt::Horizontal).first()->setRange(0,chartX);
    chart1->axes(Qt::Vertical).first()->setRange(-chartY,chartY);
    chart1->axes(Qt::Horizontal).first()->setTitleText("Czas");
    chart1->axes(Qt::Vertical).first()->setTitleText("Wartość");
    chart->axes(Qt::Horizontal).first()->setTitleText("Czas");

    chartView1 = new QChartView(chart1);
    chartView1->setRenderHint(QPainter::Antialiasing);
    chartView1->setMinimumSize(300,200);
    chartView1->setMaximumSize(1500,400);
    chart->axes(Qt::Vertical).first()->setTitleFont(font);
    chart1->axes(Qt::Vertical).first()->setTitleFont(font);
    chart2->axes(Qt::Vertical).first()->setTitleFont(font);

    chart->axes(Qt::Horizontal).first()->setTitleFont(font);
    chart1->axes(Qt::Horizontal).first()->setTitleFont(font);
    chart2->axes(Qt::Horizontal).first()->setTitleFont(font);
    chartView->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    chartView1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    chartView2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->layout_wykres1->update();
    ui->layout_wykres2->update();

    ui->layout_wykres1->addWidget(chartView,1);
    ui->layout_wykres2->addWidget(chartView1,1);
    ui->layout_wykres2->addWidget(chartView2,1);

    seriesR->points().resize(100);
    seriesZ->points().resize(100);
    seriesU->points().resize(100);
    seriesP->points().resize(100);
    seriesI->points().resize(100);
    seriesD->points().resize(100);



}
void MainWindow::ustawienieWykresowSerwer(){
    chartView1->hide();
    ui->layout_wykres1->setStretch(0,1);
    ui->layout_wykres2->setStretch(1,1);
    ui->layout_wykres2->setStretch(2,0);
    chart2->setTitle("Wykres wartości Sterującej");
    seriesP->hide();
    seriesD->hide();
    seriesI->hide();
    seriesSterowanie->show();
    wykresSchowany=true;


}
void::MainWindow::ponowneUstawienieWykresow(){
    ui->layout_wykres1->setStretch(0,1);
    ui->layout_wykres2->setStretch(0,1);
    ui->layout_wykres2->setStretch(1,1);
    chartView1->show();
    chart2->setTitle("Wykres PID");
    seriesP->show();
    seriesD->show();
    seriesI->show();
    seriesSterowanie->hide();
    wykresSchowany=false;
}

