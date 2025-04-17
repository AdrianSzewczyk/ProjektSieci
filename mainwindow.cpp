
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
    symulator = sym;
    ui->setupUi(this);
    QFont font;
    font.setPointSize(8);
    seriesZ = new QLineSeries();
    seriesZ->setName("Wartość zadana");
    seriesR = new QLineSeries();
    seriesR->setName("Wartość regulowana");
    seriesZ->append(0,0);
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
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    seriesP = new QLineSeries();
    seriesP->setName("Część proporcjonalna");
    //Wykres części całkującej sterowania
    seriesI = new QLineSeries();
    seriesI->setName("Część całkująca");
    //Wykres części całkującej sterowania
    seriesD = new QLineSeries();
    seriesD->setName("Część różniczkująca");

    chart2 = new QChart();
    chart2->setTitle("Wykres części proporcjonalnej sterowania");
    chart2->legend()->setVisible(true);
    chart2->addSeries(seriesP);
    chart2->addSeries(seriesI);
    chart2->addSeries(seriesD);
    chart2->createDefaultAxes();
    chart2->axes(Qt::Horizontal).first()->setRange(0,chartX);
    chart2->axes(Qt::Vertical).first()->setRange(-chartY,chartY);
    chart2->axes(Qt::Horizontal).first()->setTitleText("Czas");
    chart2->axes(Qt::Vertical).first()->setTitleText("Wartość");
    QChartView * chartView2 = new QChartView(chart2);
    chartView2->setRenderHint(QPainter::Antialiasing);

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

    QChartView * chartView1 = new QChartView(chart1);
    chartView1->setRenderHint(QPainter::Antialiasing);

    chart->axes(Qt::Vertical).first()->setTitleFont(font);
    chart1->axes(Qt::Vertical).first()->setTitleFont(font);
    chart2->axes(Qt::Vertical).first()->setTitleFont(font);

    chart->axes(Qt::Horizontal).first()->setTitleFont(font);
    chart1->axes(Qt::Horizontal).first()->setTitleFont(font);
    chart2->axes(Qt::Horizontal).first()->setTitleFont(font);

    ui->layout_wykres1->addWidget(chartView);
    ui->layout_wykres2->addWidget(chartView1);
    ui->layout_wykres2->addWidget(chartView2);
    ui->arxA_Input->setText("-0.4;");
    ui->arxB_Input->setText("0.6;");
    ui->opoznienie_Input->setText("1");

    ui->PIDwzmocnienie_Input->setText("1");
    ui->PIDTi_input->setText("10");
    ui->PIDTd_input->setText("0.1");

    ui->GenAmp_input->setText("1");
    ui->GenT_Input->setText("10");
    ui->GenFill_Input->setText("0.5");
    ui->interwal_Input->setText("0.043");
    ui->zaklocenia_Input->setText("0");
    seriesR->points().resize(100);
    seriesZ->points().resize(100);
    seriesU->points().resize(100);
    seriesP->points().resize(100);
    seriesI->points().resize(100);
    seriesD->points().resize(100);
    timer->setInterval(34);
    connect(timer,SIGNAL(timeout()),this,SLOT(simulationProgress()));
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


    //Sieć i nasze zmiany
    serwer = nullptr;
    serwerWlaczony=false;
    menu = new QMenu(this);
    menu->addAction("Serwer");
    menu->addAction("Klient");
    menu->setFixedWidth(ui->WyborRoli->width());
    ui->WyborRoli->setMenu(menu);
    ui->WyborRoli->setPopupMode(QToolButton::InstantPopup);

    ui->Przesylanie->setEnabled(false);
    ui->WyborRoli->setEnabled(false);
    ui->btnWlacz->setEnabled(false);
    ui->btnWyslij->setEnabled(false);
    ui->DanePrzeslij->setEnabled(false);
    ui->DaneDoPolaczenia->setEnabled(false);
    ui->statusPolaczony->setStyleSheet("QLabel { color: rgb(160, 160, 160); }");


    //Sieć Klient
    setZarzadzanieSiec();
    klientPołączony=false;
    serwerPołączony=false;

    danePobierane = new DanePobierane(this);

    SerwerJuzWystartowal=false;
    numerRamki=0;
    connect(timer,&QTimer::timeout,this,&MainWindow::WysylanieRamki);
    connect(&siec,&ZarzadzanieSiec::daneSymulacji,this,&MainWindow::DaneSymulacjiOdSerwera);
    connect(serwer,&TCPserwer::daneDoPrzetworzenia,this,&MainWindow::ObliczeniaObiektu);


}
void MainWindow::on_reset_button_clicked()
{
    timer->stop();
    symulator->set_arx({0} ,{0},1,0);
    symulator->set_pid(0,0,0);
    symulator->set_gen(0,0,0);

    chartPos = 0;
    chartPos_zero = 0;
    chartX = 100;
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
    seriesR->clear();
    seriesZ->clear();
    seriesU->clear();
    seriesP->clear();
    seriesI->clear();
    seriesD->clear();
    chart->update();
    chart1->update();
    chart2->update();

    ui->start_button->setEnabled(1);
    ui->save_button->setEnabled(1);
    ui->load_button->setEnabled(1);
}
MainWindow::~MainWindow()
{

}

void MainWindow::on_start_button_clicked()
{
    ui->start_button->setEnabled(0);
    ui->save_button->setEnabled(0);
    ui->load_button->setEnabled(0);

    std::vector<double> arxA_val = {};
    arxA_val = dane.wektor_A;
    /*if(!ui->arxA_Input->text().isEmpty())
    {
        QStringList arxA = ui->arxA_Input->text().split(u';');

        for(auto var: arxA)
        {
            arxA_val.push_back(var.toDouble());
        }
    }else arxA_val ={0};
    */
    std::vector<double> arxB_val = {};
    arxB_val = dane.wektor_B;
    /*
    if(!ui->arxB_Input->text().isEmpty())
    {
        QStringList arxB = ui->arxB_Input->text().split(u';');

        for(auto var: arxB)
        {
            arxB_val.push_back(var.toDouble());
        }
    }else arxB_val ={0};
    */
    int opoznienie = 1;
    opoznienie = dane.opoznienie;
    /*
    if (!ui->opoznienie_Input->text().isEmpty())
    {
        opoznienie = ui->opoznienie_Input->text().toInt();
    }
    */
    double disturbance_amp = 0.0;
    disturbance_amp = dane.blad;
    /*
    if (!ui->zaklocenia_Input->text().isEmpty())
    {
        disturbance_amp = ui->zaklocenia_Input->text().toDouble();
        if (disturbance_amp < 0)
        {
            // Jeśli wartość jest ujemna, ustaw wartość domyślną (0.0)
             disturbance_amp = 0.0;
        }
    }
    else
    {
     disturbance_amp = 0.0;
    }
    */
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
    timer->start();

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
}
void MainWindow::simulationProgress()
{

    if(chartPos > chartX) chartX++;
    chart->axes(Qt::Horizontal).first()->setRange(chartPos_zero+1,chartX);
    chart1->axes(Qt::Horizontal).first()->setRange(chartPos_zero+1,chartX);
    chart2->axes(Qt::Horizontal).first()->setRange(chartPos_zero+1,chartX);

    symulator->simulate();
    seriesR->append(chartPos,symulator->get_arx_val());
    seriesZ->append(chartPos,symulator->get_gen_val());
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

    }

    //int count = 0;
    if(chartPos % 10 == 0)
    {
        val_chart_1 = 0.0;
        val_chart_2 = 0.0;
        val_chart_3 = 0.0;
        val_chart_1_min = 0.0;
        val_chart_2_min = 0.0;
        val_chart_3_min = 0.0;
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
        //count++;
    }

    foreach (QPointF val_Z, seriesZ->points())
    {
        if(val_chart_1 < val_Z.y()) val_chart_1=val_Z.y();
        if(val_chart_1_min > val_Z.y()) val_chart_1_min=val_Z.y();
        //count++;
    }


    foreach (QPointF val_U, seriesU->points())
    {
        if(val_chart_2 < val_U.y()) val_chart_2=val_U.y();
        if(val_chart_2_min > val_U.y()) val_chart_2_min=val_U.y();
         //count++;
    }

    foreach (QPointF val_P, seriesP->points())
    {
        if(val_chart_3 < val_P.y()) val_chart_3=val_P.y();
        if(val_chart_3_min > val_P.y()) val_chart_3_min=val_P.y();
         //count++;
    }
    foreach (QPointF val_I, seriesI->points())
    {
        if(val_chart_3 < val_I.y()) val_chart_3=val_I.y();
         if(val_chart_3_min > val_I.y()) val_chart_3_min=val_I.y();
          //count++;
    }
    foreach (QPointF val_D, seriesD->points())
    {
        if(val_chart_3 < val_D.y()) val_chart_3=val_D.y();
         if(val_chart_3_min > val_D.y()) val_chart_3_min=val_D.y();
          //count++;
    }

    //qDebug()<<count;


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
    chart_PID_scale = val_chart_3 * 1.1;
    chart_PID_scale_below = val_chart_3_min * 1.1;



    chart->axes(Qt::Vertical).first()->setRange(chart_Zadany_scale_below,chart_Zadany_scale);
    chart1->axes(Qt::Vertical).first()->setRange(chart_Uchyb_scale_below,chart_Uchyb_scale);
    chart2->axes(Qt::Vertical).first()->setRange(chart_PID_scale_below,chart_PID_scale);

    chart->update();
    chart1->update();
    chart2->update();

}

void MainWindow::on_stop_button_clicked()
{
    timer->stop();
    ui->start_button->setEnabled(1);
    ui->save_button->setEnabled(1);
    ui->load_button->setEnabled(1);

}


void MainWindow::on_save_button_clicked()
{
   // symulator->save_config();
}


void MainWindow::on_load_button_clicked()
{
    /*
    symulator->read_config();
    QString str1={};
    for(auto y : symulator->get_arx()->get_vector_A())
    {
        str1.append(QString::number(y));
    }
    QString str2={};
    for(auto y : symulator->get_arx()->get_vector_B())
    {
        str2.append(QString::number(y));
    }
    ui->arxA_Input->setText(str1);
    ui->arxB_Input->setText(str2);
    ui->opoznienie_Input->setText(QString::number(symulator->get_arx()->get_latency()));

    ui->PIDwzmocnienie_Input->setText(QString::number(symulator->get_pid()->get_k()));
    ui->PIDTi_input->setText(QString::number(symulator->get_pid()->get_Ti()));
    ui->PIDTd_input->setText(QString::number(symulator->get_pid()->get_Td()));

    ui->GenAmp_input->setText(QString::number(symulator->get_gen()->get_Amp()));
    ui->GenT_Input->setText(QString::number(symulator->get_gen()->get_T()));
    ui->GenFill_Input->setText(QString::number(symulator->get_gen()->get_fill()));
    ui->zaklocenia_Input->setText(QString::number(symulator->get_arx()->get_disruption_amplitude()));
*/
}



void MainWindow::on_arxA_Input_editingFinished()
{
    /*
    std::vector<double> arxA_val = {};
    if(!ui->arxA_Input->text().isEmpty())
    {
        QStringList arxA = ui->arxA_Input->text().split(u';');

        for(auto var: arxA)
        {
            arxA_val.push_back(var.toDouble());
        }
    }else arxA_val ={0};
    symulator->get_arx()->set_vector_A(arxA_val);
*/
}


void MainWindow::on_arxB_Input_editingFinished()
{
    /*
    std::vector<double> arxB_val = {};
    if(!ui->arxB_Input->text().isEmpty())
    {
        QStringList arxB = ui->arxB_Input->text().split(u';');

        for(auto var: arxB)
        {
            arxB_val.push_back(var.toDouble());
        }
    }else arxB_val ={0};
    symulator->get_arx()->set_vector_B(arxB_val);
*/
}


void MainWindow::on_opoznienie_Input_editingFinished()
{
/*
    int opoznienie = 1;
    if (!ui->opoznienie_Input->text().isEmpty())
    {
        opoznienie = ui->opoznienie_Input->text().toInt();
    }
    symulator->get_arx()->set_latency(opoznienie);
*/

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


void MainWindow::on_zaklocenia_Input_editingFinished()
{
    /*
    double disturbance_amp = 0.0;
    if (!ui->zaklocenia_Input->text().isEmpty())
    {
        disturbance_amp = ui->zaklocenia_Input->text().toDouble();
        if (disturbance_amp < 0)
        {
            disturbance_amp = 0.0;
        }
        symulator->get_arx()->set_disruption_amplitude(disturbance_amp);
    }
    */
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
    //delete okno;
}


//Sieć Serwer i ogólne ustawienia

void MainWindow::on_btnWlacz_clicked()
{
    if(wybor=="Serwer"){
        if(port>0){
            if(serwer==nullptr)
            {   if(!klikniete){

                ui->btnWlacz->setText("Wyłącz");
                    serwer = new TCPserwer(this,port);
                }

                connect(serwer, &TCPserwer::newClientConnected, this, &MainWindow::on_NewClientConnected);
                connect(serwer, &TCPserwer::dataReceived, this, &MainWindow::clientDataReceived);
                connect(serwer, &TCPserwer::clientDisconnect, this, &MainWindow::clientDisconnected);
                klikniete = true;
            }else{
                ui->btnWlacz->setText("Włącz");
                delete serwer;
                serwer=nullptr;
                klikniete = false;
            }
        }
        else{
            QMessageBox::warning(this,"Błąd","Nie wybrałeś portu");
        }

    }else if(wybor=="Klient"){
        if(siec.isConnected()){
            siec.disconnect();
        }
        else{
            //QHostAddress ip;
            //QString ipAddress = "172.168.1.33";
            QString ipAddress = "127.0.0.1";
            // QHostAddress ip(ipAddress);
            //auto port = 12345;
            siec.connectToDevice(adres,port);
        }
    }else{
        QMessageBox::warning(this,"Uwaga","Nie wybrałeś roli programu");
    }




}

void MainWindow::on_NewClientConnected()
{
    klientPołączony=true;
    ui->statusPolaczony->setText("Połączony");
    ui->statusPolaczony->setStyleSheet("QLabel { color : green; }");
    qDebug() << "Klient się połączył";
}


void MainWindow::on_btnWyslij_clicked()
{
    if(serwerPołączony||klientPołączony){
        if(wybor=="Serwer"){
            auto message = ui->DanePrzeslij->text().trimmed();
            serwer->sendToAll(message);
        }else if(wybor=="Klient"){
            auto message = ui->DanePrzeslij->text().trimmed();
            siec.send(message);
        }else{
            QMessageBox::warning(this,"Błąd","Nie wybrałeś roli programu");
        }
    }else{
        QMessageBox::warning(this,"Błąd","Nie nawiązano połączenia");
    }

    ui->DanePrzeslij->clear();

}

void MainWindow::clientDisconnected(){
    qDebug()<<"Klient rozłączony";
    klientPołączony=false;
    ui->statusPolaczony->setText("Niepołączony");
    ui->statusPolaczony->setStyleSheet("QLabel { color : red; }");
}
void MainWindow::clientDataReceived(QString message){
    qDebug()<<message;
}

void MainWindow::on_WyborRoli_clicked()
{


    ui->WyborRoli->showMenu();
}


void MainWindow::on_trybSieciowy_checkStateChanged(const Qt::CheckState &arg1)
{
    bool czyTrybSieciowy = (bool)arg1;
    if(czyTrybSieciowy==true){
        ui->Przesylanie->setEnabled(true);
        ui->WyborRoli->setEnabled(true);
        ui->btnWlacz->setEnabled(true);
        ui->btnWyslij->setEnabled(true);
        ui->DanePrzeslij->setEnabled(true);
        ui->DaneDoPolaczenia->setEnabled(true);
        ui->statusPolaczony->setStyleSheet("QLabel { color : red; }");
        klikniete=false;

        connect(danePobierane,&DanePobierane::PrzesylanieDanych,this,&MainWindow::PrzypisanieAdresuIportu);
        connect(danePobierane,&DanePobierane::BledneDane,this,&MainWindow::BledneDane);



    }else if(czyTrybSieciowy==false){
        ui->Przesylanie->setEnabled(false);
        ui->WyborRoli->setEnabled(false);
        ui->WyborRoli->setText("Wybierz");
        ui->btnWlacz->setEnabled(false);
        ui->btnWlacz->setText("Włącz");
        ui->btnWyslij->setEnabled(false);
        ui->DanePrzeslij->setEnabled(false);
        ui->DaneDoPolaczenia->setEnabled(false);
        klientPołączony=false;
        serwerPołączony=false;
        ui->statusPolaczony->setText("Niepołączony");
        ui->statusPolaczony->setStyleSheet("QLabel { color: rgb(160, 160, 160); }");

        disconnect(danePobierane,&DanePobierane::PrzesylanieDanych,this,&MainWindow::PrzypisanieAdresuIportu);
        disconnect(danePobierane,&DanePobierane::BledneDane,this,&MainWindow::BledneDane);

        siec.disconnect();
        delete serwer;
        serwer=nullptr;
        wybor="Nikt";
        danePobierane->UstawienieDostepnosci(wybor);
        danePobierane->Czyszczenie();

        ui->box_pid->setEnabled(true);
        ui->box_add->setEnabled(true);
        ui->box_gen->setEnabled(true);
        SerwerJuzWystartowal=false;
        klikniete=false;
        ui->box_arx->setEnabled(true);
        ui->start_button->setEnabled(true);
        ui->reset_button->setEnabled(true);
        ui->Tryb_I->setEnabled(true);
        ui->PID_reset_I->setEnabled(true);
        ui->stop_button->setEnabled(true);
    }
}


void MainWindow::on_WyborRoli_triggered(QAction *arg1)
{
    wybor = arg1->text();
    if(wybor=="Serwer"){
        ui->btnWlacz->setText("Włącz");
        ui->WyborRoli->setText("Serwer");


        ui->box_pid->setEnabled(false);
        ui->box_add->setEnabled(false);
        ui->box_gen->setEnabled(false);
        ui->box_arx->setEnabled(true);

        ui->start_button->setEnabled(false);
        ui->reset_button->setEnabled(false);
        ui->Tryb_I->setEnabled(false);
        ui->PID_reset_I->setEnabled(false);
        ui->stop_button->setEnabled(false);

    }else if(wybor=="Klient"){
        ui->btnWlacz->setText("Połącz");
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
    connect(&siec,&ZarzadzanieSiec::connected,this,&MainWindow::siec_connected);
    connect(&siec,&ZarzadzanieSiec::disconnected,this,&MainWindow::siec_disconnected);
    connect(&siec,&ZarzadzanieSiec::stateChanged,this,&MainWindow::siec_stateChanged);
    connect(&siec,&ZarzadzanieSiec::errorOccurred,this,&MainWindow::siec_errorOccurred);
    connect(&siec,&ZarzadzanieSiec::dataReady,this,&MainWindow::siec_dataReady);
}


void MainWindow::siec_connected(){

    qDebug("Podłączono");
    ui->btnWlacz->setText("Rozłącz");
    serwerPołączony=true;
    ui->statusPolaczony->setText("Połączony");
    ui->statusPolaczony->setStyleSheet("QLabel { color : green; }");
    //ui->PrzesylanieDanych->setEnabled(true);
    //ui->wiadomoscWysylana->setEnabled(true);
    //ui->Send->setEnabled(true);

}
void MainWindow::siec_disconnected(){

    qDebug("Rozłączono");
    ui->btnWlacz->setText("Połącz");
    serwerPołączony=false;
    ui->statusPolaczony->setText("Niepołączony");
    ui->statusPolaczony->setStyleSheet("QLabel { color : red; }");


    //ui->PrzesylanieDanych->setEnabled(false);

}
void MainWindow::siec_stateChanged(QAbstractSocket::SocketState state){

    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    qDebug() << metaEnum.valueToKey(state);
}
void MainWindow::siec_errorOccurred(QAbstractSocket::SocketError error){

    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketError>();
    qDebug() << metaEnum.valueToKey(error);
}




void MainWindow::siec_dataReady(QByteArray data){
    qDebug()<<(QString)data;
}





void MainWindow::on_DaneDoPolaczenia_clicked()
{
    danePobierane->exec();
}

void MainWindow::PrzypisanieAdresuIportu(QString a,quint16 p){

    adres=a;
    port=p;
    if(SerwerJuzWystartowal){
        delete serwer;
        serwer = new TCPserwer(this,port);

    }
    SerwerJuzWystartowal=true;



}
void MainWindow::BledneDane(){
    QMessageBox::warning(this,"Błąd","Błedne Dane");
}

void MainWindow::WysylanieRamki(){
    siec.WyslijWiadomoscDoSerwera(numerRamki, st, intCzas, wartoscSterujaca);
}

void MainWindow::DaneSymulacjiOdSerwera(int n,double w){
    numerRamki=n;
    wartoscReg=w;
}

void MainWindow::ObliczeniaObiektu(int nrRamki,StanSymulacji s,double i, double w){

}
