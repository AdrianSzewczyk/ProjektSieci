
#include "mainwindow.h"
#include <QApplication>
#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include "mainwindow.h"
#include "Symulator.h"

MainWindow::MainWindow(QWidget *parent,Symulator *sym)
    : QMainWindow(parent),timer(new QTimer(this)),ui(new Ui::MainWindow)
{
    symulator = sym;
    ui->setupUi(this);

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
    chart->axes(Qt::Vertical).first()->setRange(0,chartY);
    chart->setVisible(true);

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
    chart2->axes(Qt::Vertical).first()->setRange(0,chartY);

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
    chart1->axes(Qt::Vertical).first()->setRange(0,chartY);

    QChartView * chartView1 = new QChartView(chart1);
    chartView1->setRenderHint(QPainter::Antialiasing);


    ui->layout_wykres1->addWidget(chartView);
    ui->layout_wykres2->addWidget(chartView1);
    ui->layout_wykres2->addWidget(chartView2);
    timer->setInterval(34);
    connect(timer,SIGNAL(timeout()),this,SLOT(simulationProgress()));

}
void MainWindow::on_reset_button_clicked()
{
    timer->stop();
    symulator->set_arx({0} ,{0},0,0);
    symulator->set_pid(0,0,0);
    symulator->set_gen(0,0,0);
    seriesR->clear();
    seriesZ->clear();
    seriesU->clear();
    seriesP->clear();
    seriesI->clear();
    seriesD->clear();
    chartPos = 0;
    chartPos_zero = 0;
    chartX = 100;
    chart->axes(Qt::Horizontal).first()->setRange(chartPos_zero,chartX);
    chart1->axes(Qt::Horizontal).first()->setRange(chartPos_zero,chartX);
    chart2->axes(Qt::Horizontal).first()->setRange(chartPos_zero,chartX);

    chart->update();
    chart1->update();
    chart2->update();
    symulator->get_pid()->reset_Derivative();
    symulator->get_pid()->reset_Intergral();

    ui->start_button->setEnabled(1);
}
MainWindow::~MainWindow()
{

}

void MainWindow::on_start_button_clicked()
{
    ui->start_button->setEnabled(0);

    std::vector<double> arxA_val = {};
    if(!ui->arxA_Input->text().isEmpty())
    {
        QStringList arxA = ui->arxA_Input->text().split(u',');

        for(auto var: arxA)
        {
            arxA_val.push_back(var.toDouble());
        }
    }else arxA_val ={0};

    std::vector<double> arxB_val = {};
    if(!ui->arxB_Input->text().isEmpty())
    {
        QStringList arxB = ui->arxB_Input->text().split(u',');

        for(auto var: arxB)
        {
            arxB_val.push_back(var.toDouble());
        }
    }else arxB_val ={0};

    if(!ui->opoznienie_Input->text().isEmpty())
    {
    symulator->set_arx(arxA_val
                           ,arxB_val
                           ,ui->opoznienie_Input->text().toInt()
                           ,ui->zaklocenia_button->isChecked());
    }

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
    qDebug()<<"OK";
}

void MainWindow::simulationProgress()
{

    if(chartPos > chartX) chartX++;
    chart->axes(Qt::Horizontal).first()->setRange(chartPos_zero,chartX);
    chart1->axes(Qt::Horizontal).first()->setRange(chartPos_zero,chartX);
    chart2->axes(Qt::Horizontal).first()->setRange(chartPos_zero,chartX);

    symulator->simulate();
    seriesR->append(chartPos,symulator->get_arx_val());
    seriesZ->append(chartPos,symulator->get_gen_val());
    seriesU->append(chartPos,symulator->get_pid()->get_diff());
    seriesP->append(chartPos,symulator->get_pid()->proportional_control());
    seriesI->append(chartPos,symulator->get_pid()->integral_control());
    seriesD->append(chartPos,symulator->get_pid()->derivative_control());
    chartPos++;

    if(chartPos >= 100) chartPos_zero++;



    chart->update();
    chart1->update();
    chart2->update();

}

void MainWindow::on_stop_button_clicked()
{
    timer->stop();
    ui->start_button->setEnabled(1);
}

