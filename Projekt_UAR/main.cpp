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

QT_USE_NAMESPACE

    int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Główne okno aplikacji
    QMainWindow window;
    QWidget *centralWidget = new QWidget(&window);
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
    window.setCentralWidget(centralWidget);
    window.setWindowTitle("Symulator z wykresami");
    window.resize(1500, 1000);
    window.show();

    return a.exec();
}

/* STARY KOD
#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
QT_USE_NAMESPACE

    int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QVBoxLayout *layout = new QVBoxLayout();

    // Wartość zadana/regulowana
    QLineSeries *seriesZ = new QLineSeries();
    seriesZ->append(0, 0);
    seriesZ->append(1, 3.5);
    seriesZ->append(2, 4);
    seriesZ->append(3, 2.6);
    seriesZ->append(4, 3);
    seriesZ->append(5, 2.9);
    seriesZ->append(6, 2.9);
    seriesZ->append(7, 3.2);

    QLineSeries *seriesR = new QLineSeries();
    seriesR->append(0, 0);
    seriesR->append(1, 2);
    seriesR->append(2, 2.5);
    seriesR->append(3, 3.0);
    seriesR->append(4, 3.5);
    seriesR->append(5, 3.2);
    seriesR->append(6, 3);
    seriesR->append(7, 3);

    seriesZ->setName("Wartość zadana");
    seriesR->setName("Wartość regulowana");

    QChart *chart = new QChart();
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chart->addSeries(seriesZ);
    chart->addSeries(seriesR);

    chart->setTitle("Wykres wartości zadanej i regulowanej");
    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);

    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Kroki symulacji");
    axisX->setLabelFormat("%d");

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Wartości");
    axisY->setLabelFormat("%.1f");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    seriesZ->attachAxis(axisX);
    seriesZ->attachAxis(axisY);
    seriesR->attachAxis(axisX);
    seriesR->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Wykres uchybu
    QLineSeries *seriesU = new QLineSeries();
    seriesU->append(0, 0);
    seriesU->append(1, 0.03);
    seriesU->append(2, 0.04);
    seriesU->append(3, 0.05);
    seriesU->append(4, 0.051);
    seriesU->append(5, 0.06);
    seriesU->append(6, 0.06);

    seriesU->setName("Uchyb");

    QChart *chart1 = new QChart();
    chart1->legend()->setVisible(true);
    chart1->legend()->setAlignment(Qt::AlignBottom);

    chart1->addSeries(seriesU);

    chart1->setTitle("Wykres uchybu");
    chart1->setTitleFont(font);

    QValueAxis *axisX1 = new QValueAxis();
    axisX1->setTitleText("Kroki symulacji");
    axisX1->setLabelFormat("%d");

    QValueAxis *axisY1 = new QValueAxis();
    axisY1->setTitleText("Uchyb");
    axisY1->setLabelFormat("%.3f");

    chart1->addAxis(axisX1, Qt::AlignBottom);
    chart1->addAxis(axisY1, Qt::AlignLeft);

    seriesU->attachAxis(axisX1);
    seriesU->attachAxis(axisY1);

    QChartView *chartView1 = new QChartView(chart1);
    chartView1->setRenderHint(QPainter::Antialiasing);

    // Wykres sterowania
    QLineSeries *seriesST = new QLineSeries();
    seriesST->append(0, 0);
    seriesST->append(1, 0.5);
    seriesST->append(2, 1);
    seriesST->append(3, 2.25);
    seriesST->append(4, 3.3);
    seriesST->append(5, 3.5);
    seriesST->append(6, 5);

    seriesST->setName("Wartość sterowania");

    QChart *chart2 = new QChart();
    chart2->legend()->setVisible(true);
    chart2->legend()->setAlignment(Qt::AlignBottom);

    chart2->addSeries(seriesST);

    chart2->setTitle("Wykres sterowania");
    chart2->setTitleFont(font);

    QValueAxis *axisX2 = new QValueAxis();
    axisX2->setTitleText("Kroki symulacji");
    axisX2->setLabelFormat("%d");

    QValueAxis *axisY2 = new QValueAxis();
    axisY2->setTitleText("Sterowanie");
    axisY2->setLabelFormat("%.2f");

    chart2->addAxis(axisX2, Qt::AlignBottom);
    chart2->addAxis(axisY2, Qt::AlignLeft);

    seriesST->attachAxis(axisX2);
    seriesST->attachAxis(axisY2);

    QChartView *chartView2 = new QChartView(chart2);
    chartView2->setRenderHint(QPainter::Antialiasing);

    layout->addWidget(chartView);
    layout->addWidget(chartView1);
    layout->addWidget(chartView2);

    QMainWindow window;
    QWidget *centralWidget = new QWidget(&window);
    centralWidget->setLayout(layout);

    window.setCentralWidget(centralWidget);
    window.setWindowTitle("Symulator -> wykresy");
    window.resize(800, 600);
    window.show();

    return a.exec();
}
*/
