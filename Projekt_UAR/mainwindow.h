
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QComboBox>
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
    QLineEdit *intervalInput;
    QRadioButton *zaklocenia;
    QComboBox *typGeneratora;
    double chartX = 100;
    double chartY = 1;
    int chartPos = 0;
    int chartPos_zero = 0;
    QLineSeries *seriesZ;
    QLineSeries *seriesR;
    QChart *chart;
    QChartView *chartView;

    QLineSeries *seriesU;
    QChart *chart1;
    QChartView *chartView1;

    QLineSeries *seriesP;
    QChart *chart2;
    QChartView *chartView2;

    QLineSeries *seriesI;
    QChart *chart3;
    QChartView *chartView3;

    QLineSeries *seriesD;
    QChart *chart4;
    QChartView *chartView4;

    QVBoxLayout *inputLayout;

    // Przyciski
    QPushButton *simulateButton;
    QPushButton *stopButton;
    QPushButton *simulationReset;
    // Symulator
    Symulator* symulator;
    QTimer *timer = nullptr;
};

#endif // MAINWINDOW_H

