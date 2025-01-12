
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

    // Sekcja pól wprowadzania i przycisków
    QVBoxLayout *inputLayout = new QVBoxLayout();
    QGroupBox *inputGroup = new QGroupBox("Parametry symulacji", centralWidget);

    QLineEdit *arxAInput = new QLineEdit();
    QLineEdit *arxBInput = new QLineEdit();
    QLineEdit *pidKInput = new QLineEdit();
    QLineEdit *pidTiInput = new QLineEdit();
    QLineEdit *pidTdInput = new QLineEdit();
    QLineEdit *genAmpInput = new QLineEdit();
    QLineEdit *genTInput = new QLineEdit();
    QLineEdit *genFillInput = new QLineEdit();
    QPushButton *simulateButton = new QPushButton("Symuluj");
    QPushButton *stopButton = new QPushButton("Stop");
    QLabel *simulationResult = new QLabel("Wynik symulacji: 0");

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
    inputLayout->addWidget(simulateButton);
    inputLayout->addWidget(stopButton);
    inputLayout->addWidget(simulationResult);

    inputGroup->setLayout(inputLayout);

    // Sekcja wykresów
    QVBoxLayout *chartLayout = new QVBoxLayout();

    // Wykres wartości zadanej i regulowanej
    QLineSeries *seriesZ = new QLineSeries();
    seriesZ->setName("Wartość zadana");
    QLineSeries *seriesR = new QLineSeries();
    seriesR->setName("Wartość regulowana");

    // Dodanie arbitralnych wartości


    QChart *chart = new QChart();
    chart->addSeries(seriesZ);
    chart->addSeries(seriesR);
    chart->setTitle("Wykres wartości zadanej i regulowanej");
    chart->legend()->setVisible(true);

    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Kroki symulacji");
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Wartości");
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    seriesZ->attachAxis(axisX);
    seriesR->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartLayout->addWidget(chartView);

    // Wykres uchybu
    QLineSeries *seriesU = new QLineSeries();
    seriesU->setName("Uchyb");



    QChart *chart1 = new QChart();
    chart1->addSeries(seriesU);
    chart1->setTitle("Wykres uchybu");
    chart1->legend()->setVisible(true);

    QValueAxis *axisX1 = new QValueAxis();
    axisX1->setTitleText("Kroki symulacji");
    QValueAxis *axisY1 = new QValueAxis();
    axisY1->setTitleText("Uchyb");
    chart1->addAxis(axisX1, Qt::AlignBottom);
    chart1->addAxis(axisY1, Qt::AlignLeft);
    seriesU->attachAxis(axisX1);
    seriesU->attachAxis(axisY1);

    QChartView *chartView1 = new QChartView(chart1);
    chartView1->setRenderHint(QPainter::Antialiasing);
    chartLayout->addWidget(chartView1);

    // Wykres sterowania
    QLineSeries *seriesST = new QLineSeries();
    seriesST->setName("Wartość sterowania");



    QChart *chart2 = new QChart();
    chart2->addSeries(seriesST);
    chart2->setTitle("Wykres sterowania");
    chart2->legend()->setVisible(true);

    QValueAxis *axisX2 = new QValueAxis();
    axisX2->setTitleText("Kroki symulacji");
    QValueAxis *axisY2 = new QValueAxis();
    axisY2->setTitleText("Sterowanie");
    chart2->addAxis(axisX2, Qt::AlignBottom);
    chart2->addAxis(axisY2, Qt::AlignLeft);
    seriesST->attachAxis(axisX2);
    seriesST->attachAxis(axisY2);

    QChartView *chartView2 = new QChartView(chart2);
    chartView2->setRenderHint(QPainter::Antialiasing);
    chartLayout->addWidget(chartView2);

    // Dodanie sekcji do głównego layoutu
    mainLayout->addWidget(inputGroup, 1);
    mainLayout->addLayout(chartLayout, 3);



    // Finalizacja
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    connect(timer,SIGNAL(timeout()),this,SLOT(simulationProgress()));
    //connect(simulateButton, SIGNAL(clicked()),this,SLOT(on_simulateButton_clicked_test()));
    connect(simulateButton, &QPushButton::clicked, this, &MainWindow::on_simulateButton_clicked_test);
};

MainWindow::~MainWindow()
{
}
void MainWindow::on_simulateButton_clicked_test()
{
    simulateButton->setEnabled(0);
    if(symulator != nullptr)
    symulator->set_arx({-0.4} ,{0.6},1,false);
    symulator->set_pid(1,10,3);
    symulator->set_gen(1,1,1);
    symulator->set_generator_type(typ_generatora::gen_Skok);
    qDebug()<<"OK";
    timer->start();
}
void MainWindow::on_stopButton_clicked()
{
    timer->stop();
    simulateButton->setEnabled(1);

}
void MainWindow::simulationProgress()
{
    simulationResult->text()= QString::number( symulator->simulate());
    qDebug()<<symulator->simulate();
}
/* STARY KOD
 * #include "mainwindow.h"
#include <QMessageBox>
#include <QtCharts/QChart>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), symulator({-0.4}, {0.6}, 1, false, 1.0, 1.0, 1.0, 1.0, 1, 0.5)
{
    // Inicjalizacja pól wprowadzania danych
    arxAInput = new QLineEdit(this);
    arxBInput = new QLineEdit(this);
    pidKInput = new QLineEdit(this);
    pidTiInput = new QLineEdit(this);
    pidTdInput = new QLineEdit(this);
    genStepInput = new QLineEdit(this);
    genSinInput = new QLineEdit(this);
    genSquareInput = new QLineEdit(this);

    simulationResult = new QLabel("Wynik symulacji: 0", this);

    simulateButton = new QPushButton("Symuluj", this);

    // Inicjalizacja wykresu
    setpointSeries = new QLineSeries();
    setpointSeries->setName("Wartość zadana");

    controlSeries = new QLineSeries();
    controlSeries->setName("Wartość regulowana");

    QChart *chart = new QChart();
    chart->addSeries(setpointSeries);
    chart->addSeries(controlSeries);

    chart->createDefaultAxes();
    chart->setTitle("Wykres wartości zadanej i regulowanej");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    axisX = new QValueAxis();
    axisX->setTitleText("Kroki symulacji");
    axisX->setLabelFormat("%d");
    axisX->setTickCount(11);
    chart->setAxisX(axisX, setpointSeries);
    chart->setAxisX(axisX, controlSeries);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Wartości");
    axisY->setLabelFormat("%.2f");
    chart->setAxisY(axisY, setpointSeries);
    chart->setAxisY(axisY, controlSeries);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Layout
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->addWidget(new QLabel("ARX - Współczynnik A:"), 0, 0);
    gridLayout->addWidget(arxAInput, 0, 1);
    gridLayout->addWidget(new QLabel("ARX - Współczynnik B:"), 1, 0);
    gridLayout->addWidget(arxBInput, 1, 1);
    gridLayout->addWidget(new QLabel("PID - K:"), 2, 0);
    gridLayout->addWidget(pidKInput, 2, 1);
    gridLayout->addWidget(new QLabel("PID - Ti:"), 3, 0);
    gridLayout->addWidget(pidTiInput, 3, 1);
    gridLayout->addWidget(new QLabel("PID - Td:"), 4, 0);
    gridLayout->addWidget(pidTdInput, 4, 1);
    gridLayout->addWidget(new QLabel("Generator - Krok:"), 5, 0);
    gridLayout->addWidget(genStepInput, 5, 1);
    gridLayout->addWidget(new QLabel("Generator - Sinus:"), 6, 0);
    gridLayout->addWidget(genSinInput, 6, 1);
    gridLayout->addWidget(new QLabel("Generator - Prostokąt:"), 7, 0);
    gridLayout->addWidget(genSquareInput, 7, 1);
    gridLayout->addWidget(simulateButton, 8, 0, 1, 2);
    gridLayout->addWidget(simulationResult, 9, 0, 1, 2);
    gridLayout->addWidget(chartView, 10, 0, 1, 2);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(gridLayout);
    setCentralWidget(centralWidget);

    // Podłącz przycisk do slotu
    connect(simulateButton, &QPushButton::clicked, this, &MainWindow::processSimulation);
}

void MainWindow::processSimulation()
{
    try {
        // Pobierz dane z pól wprowadzania
        QString arxAString = arxAInput->text();
        QString arxBString = arxBInput->text();
        QString pidKString = pidKInput->text();
        QString pidTiString = pidTiInput->text();
        QString pidTdString = pidTdInput->text();
        QString genStepString = genStepInput->text();
        QString genSinString = genSinInput->text();
        QString genSquareString = genSquareInput->text();

        // Konwersja danych na odpowiednie typy
        std::vector<double> arxA = { arxAString.toDouble() };
        std::vector<double> arxB = { arxBString.toDouble() };
        double pidK = pidKString.toDouble();
        double pidTi = pidTiString.toDouble();
        double pidTd = pidTdString.toDouble();
        double genStep = genStepString.toDouble();
        double genSin = genSinString.toDouble();
        double genSquare = genSquareString.toDouble();

        // Ustaw dane w symulatorze
        symulator.set_arx(arxA, arxB, 1, false);
        symulator.set_pid(pidK, pidTi, pidTd);
        symulator.set_gen(genStep, genSin, genSquare);

        // Wyczyść wykresy
        setpointSeries->clear();
        controlSeries->clear();

        // Symulacja kroków
        for (int i = 0; i < 100; ++i) {
            double result = symulator.simulate();
            setpointSeries->append(i, 1.0);  // Wartość zadana (przykład)
            controlSeries->append(i, result);
        }

        axisX->setRange(0, 99); // Poprawienie zakresu osi X
        simulationResult->setText(QString("Wynik symulacji: %1").arg(symulator.simulate()));
    } catch (std::exception &e) {
        QMessageBox::critical(this, "Błąd", e.what());
    }
}

MainWindow::~MainWindow()
{
    delete arxAInput;
    delete arxBInput;
    delete pidKInput;
    delete pidTiInput;
    delete pidTdInput;
    delete genStepInput;
    delete genSinInput;
    delete genSquareInput;
    delete simulationResult;
    delete simulateButton;
    delete chartView;
    delete setpointSeries;
    delete controlSeries;
    delete axisX;
}
*/
