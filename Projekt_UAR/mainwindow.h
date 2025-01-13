
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include "Symulator.h"
#include "qlineseries.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QTimer>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr,Symulator *sym = nullptr);

    ~MainWindow();
private slots:
    void on_simulateButton_clicked();
    void on_stopButton_clicked();
    void simulationProgress();
private:
    // Pola do wprowadzania danych
    QLineEdit *arxAInput;
    QLineEdit *arxBInput;
    QLineEdit *pidKInput;
    QLineEdit *pidTiInput;
    QLineEdit *pidTdInput;
    QLineEdit *genAmpInput;
    QLineEdit *genTInput;
    QLineEdit *genFillInput;

    double chartX = 100;
    double chartY = 1.5;
    int chartPos = 0;
    int chartPos_zero = 0;
    QLineSeries *seriesZ;
    QLineSeries *seriesR;
    QChart *chart;
    QChartView *chartView;

    QLineSeries *seriesU;
    QChart *chart1;
    QChartView *chartView1;

    QVBoxLayout *inputLayout;
    // Wynik symulacji
    QLabel *simulationResult;

    // Przyciski
    QPushButton *simulateButton;
    QPushButton *stopButton;
    // Symulator
    Symulator* symulator;
    QTimer *timer = nullptr;
};

#endif // MAINWINDOW_H

