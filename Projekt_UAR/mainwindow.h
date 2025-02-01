
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

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr,Symulator *sym = nullptr);

    ~MainWindow();
private slots:
    /*
    void on_simulateButton_clicked();
    void on_stopButton_clicked();

    void reset();*/
    void simulationProgress();
    void on_reset_button_clicked();

    void on_start_button_clicked();

    void on_stop_button_clicked();

    void on_save_button_clicked();

    void on_load_button_clicked();

private:
    double chartX = 100;
    double chartY = 1;
    int chartPos = 0;
    int chartPos_zero = 0;

    double chart_Zadany_scale = 1;
    double chart_PID_scale = 1;
    double chart_Uchyb_scale = 1;

    double chart_Zadany_scale_below = 0;
    double chart_PID_scale_below = 0;
    double chart_Uchyb_scale_below = 0;

    QLineSeries *seriesZ;
    QLineSeries *seriesR;
    QLineSeries *seriesU;
    QLineSeries *seriesP;
    QLineSeries *seriesI;
    QLineSeries *seriesD;

    QChart *chart;
    QChart *chart1;
    QChart *chart2;

    // Symulator
    Symulator* symulator;
    QTimer *timer = nullptr;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

