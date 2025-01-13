
#include "mainwindow.h"
#include <QApplication>
#include <QMainWindow>
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
    : QMainWindow(parent),timer(new QTimer(this))
{
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    symulator = sym;
    // Sekcja pól wprowadzania i przycisków
    inputLayout = new QVBoxLayout();
    QGroupBox *inputGroup = new QGroupBox("Parametry symulacji", centralWidget);

     arxAInput = new QLineEdit();
     arxBInput = new QLineEdit();
     pidKInput = new QLineEdit();
     pidTiInput = new QLineEdit();
     pidTdInput = new QLineEdit();
     genAmpInput = new QLineEdit();
     genTInput = new QLineEdit();
     genFillInput = new QLineEdit();
     intervalInput = new QLineEdit();
     simulateButton = new QPushButton("Symuluj");
     stopButton = new QPushButton("Stop");
     simulationReset = new QPushButton("Reset");
     zaklocenia = new QRadioButton("Zakłócenia");
     typGeneratora = new QComboBox();

    typGeneratora->addItem("Skok");
    typGeneratora->addItem("Sin");
    typGeneratora->addItem("Square");
    inputLayout->addWidget(new QLabel("ARX - Współczynniki A:"));
    inputLayout->addWidget(arxAInput);
    inputLayout->addWidget(new QLabel("ARX - Współczynniki B:"));
    inputLayout->addWidget(arxBInput);
    inputLayout->addWidget(new QLabel("PID - Wzmocnienie K:"));
    inputLayout->addWidget(pidKInput);
    inputLayout->addWidget(new QLabel("PID - Stała całkowania Ti:"));
    inputLayout->addWidget(pidTiInput);
    inputLayout->addWidget(new QLabel("PID - Stała różniczkowania Td:"));
    inputLayout->addWidget(pidTdInput);
    inputLayout->addWidget(new QLabel("Generator - Amplituda:"));
    inputLayout->addWidget(genAmpInput);
    inputLayout->addWidget(new QLabel("Generator - T:"));
    inputLayout->addWidget(genTInput);
    inputLayout->addWidget(new QLabel("Generator - Fill:"));
    inputLayout->addWidget(genFillInput);
    inputLayout->addWidget(new QLabel("Typ Generatora"));
    inputLayout->addWidget(typGeneratora);
    inputLayout->addWidget(new QLabel("Interwal"));
    inputLayout->addWidget(intervalInput);
    inputLayout->addWidget(zaklocenia);
    inputLayout->addWidget(simulateButton);
    inputLayout->addWidget(stopButton);
    inputLayout->addWidget(simulationReset);
    inputGroup->setLayout(inputLayout);

    // Sekcja wykresów
    QVBoxLayout *chartLayout = new QVBoxLayout();

    // Wykres wartości zadanej i regulowanej
    seriesZ = new QLineSeries();
    seriesZ->setName("Wartość zadana");
    seriesR = new QLineSeries();
    seriesR->setName("Wartość regulowana");
    seriesZ->append(0,0);
    seriesR->append(0,0);
    // Dodanie arbitralnych wartości

    chart = new QChart();
    chart->setTitle("Wykres wartości zadanej i regulowanej");
    chart->legend()->setVisible(true);
   /* axisX = new QValueAxis();
    axisX->setTitleText("Kroki symulacji");
    axisY = new QValueAxis();
    axisY->setTitleText("Wartości");
    */


    chart->addSeries(seriesZ);
    chart->addSeries(seriesR);
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0,chartX);
    chart->axes(Qt::Vertical).first()->setRange(0,chartY);
    //chart->addAxis(axisX, Qt::AlignBottom);
    //chart->addAxis(axisY, Qt::AlignLeft);
    chart->setVisible(true);


    //seriesZ->attachAxis(axisX);
   // seriesR->attachAxis(axisY);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartLayout->addWidget(chartView);

    // Wykres uchybu
    seriesU = new QLineSeries();
    seriesU->setName("Uchyb");
    chart1 = new QChart();
    chart1->setTitle("Wykres uchybu");
    chart1->legend()->setVisible(true);
    chart1->addSeries(seriesU);
    chart1->createDefaultAxes();
    chart1->axes(Qt::Horizontal).first()->setRange(0,chartX);
    chart1->axes(Qt::Vertical).first()->setRange(0,chartY);

    chartView1 = new QChartView(chart1);
    chartView1->setRenderHint(QPainter::Antialiasing);
    chartLayout->addWidget(chartView1);

    // Wykres części proporcjonalnej sterowania
    seriesP = new QLineSeries();
    seriesP->setName("Część proporcjonalna");
    chart2 = new QChart();
    chart2->setTitle("Wykres części proporcjonalnej sterowania");
    chart2->legend()->setVisible(true);
    chart2->addSeries(seriesP);
    chart2->createDefaultAxes();
    chart2->axes(Qt::Horizontal).first()->setRange(0,chartX);
    chart2->axes(Qt::Vertical).first()->setRange(0,chartY);

    chartView2 = new QChartView(chart2);
    chartView2->setRenderHint(QPainter::Antialiasing);
    chartLayout->addWidget(chartView2);
    //Wykres części całkującej sterowania
    seriesI = new QLineSeries();
    seriesI->setName("Część całkująca");
    chart3 = new QChart();
    chart3->setTitle("Wykres części całkującej sterowania");
    chart3->legend()->setVisible(true);
    chart3->addSeries(seriesI);
    chart3->createDefaultAxes();
    chart3->axes(Qt::Horizontal).first()->setRange(0,chartX);
    chart3->axes(Qt::Vertical).first()->setRange(0,chartY);
    chartView3 = new QChartView(chart3);
    chartView3->setRenderHint(QPainter::Antialiasing);
    chartLayout->addWidget(chartView3);
    //Wykres części całkującej sterowania
    seriesD = new QLineSeries();
    seriesD->setName("Część różniczkująca");
    chart4 = new QChart();
    chart4->setTitle("Wykres części różniczkującej sterowania");
    chart4->legend()->setVisible(true);
    chart4->addSeries(seriesD);
    chart4->createDefaultAxes();
    chart4->axes(Qt::Horizontal).first()->setRange(0,chartX);
    chart4->axes(Qt::Vertical).first()->setRange(0,chartY);
    chartView4 = new QChartView(chart4);
    chartView4->setRenderHint(QPainter::Antialiasing);
    chartLayout->addWidget(chartView4);


    // Dodanie sekcji do głównego layoutu
    mainLayout->addWidget(inputGroup, 1);
    mainLayout->addLayout(chartLayout, 3);



    // Finalizacja
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    timer->setInterval(250);
    connect(timer,SIGNAL(timeout()),this,SLOT(simulationProgress()));
    //connect(simulateButton, SIGNAL(clicked()),this,SLOT(on_simulateButton_clicked_test()));
    connect(simulateButton, &QPushButton::clicked, this, &MainWindow::on_simulateButton_clicked);
    connect(stopButton, &QPushButton::clicked, this, &MainWindow::on_stopButton_clicked);
};

MainWindow::~MainWindow()
{
}
void MainWindow::on_simulateButton_clicked()
{
    simulateButton->setEnabled(0);


    symulator->set_arx({-0.4} ,{0.6},1,false);
    symulator->set_pid(1,10,0.1);
    symulator->set_gen(1,1,1);
    symulator->set_generator_type(typ_generatora::gen_Skok);
    double yaxis = 1.5*symulator->get_gen()->get_Amp();
    chart->axes(Qt::Vertical).first()->setRange(chartPos_zero, yaxis);
    chart1->axes(Qt::Vertical).first()->setRange(chartPos_zero,yaxis);
    chart2->axes(Qt::Vertical).first()->setRange(chartPos_zero,yaxis);
    timer->start();
       qDebug()<<"OK";
}
void MainWindow::on_stopButton_clicked()
{
    timer->stop();
    simulateButton->setEnabled(1);

}
void MainWindow::simulationProgress()
{
    //simulationResult->text()= QString::number( symulator->simulate());
    if(chartPos > chartX) chartX++;
    chart->axes(Qt::Horizontal).first()->setRange(chartPos_zero,chartX);
    chart1->axes(Qt::Horizontal).first()->setRange(chartPos_zero,chartX);
    chart2->axes(Qt::Horizontal).first()->setRange(chartPos_zero,chartX);
    qDebug()<<symulator->simulate();
    seriesR->append(chartPos,symulator->get_arx_val());
    seriesZ->append(chartPos,symulator->get_gen_val());
    seriesU->append(chartPos,symulator->get_pid()->get_diff());
    seriesP->append(chartPos,symulator->get_pid()->proportional_control());
    seriesI->append(chartPos,symulator->get_pid()->integral_control());
    seriesD->append(chartPos,symulator->get_pid()->derivative_control());
    chartPos++;

    if(chartPos >= 100) chartPos_zero++;


    //chart->axes(Qt::Vertical).first()->setRange(0,chartY);
    chart->update();
    chart1->update();
    chart2->update();
    chart3->update();
    chart4->update();
   // chartView->repaint();
}
