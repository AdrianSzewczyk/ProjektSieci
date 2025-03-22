
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

    void on_arxA_Input_editingFinished();

    void on_arxB_Input_editingFinished();

    void on_opoznienie_Input_editingFinished();

    void on_PIDwzmocnienie_Input_editingFinished();

    void on_PIDTi_input_editingFinished();

    void on_PIDTd_input_editingFinished();

    void on_GenAmp_input_editingFinished();

    void on_GenT_Input_editingFinished();

    void on_GenFill_Input_editingFinished();

    void on_genType_Box_currentIndexChanged(int index);

    void on_interwal_Input_editingFinished();

    void on_zaklocenia_Input_editingFinished();

    void on_Tryb_I_toggled(bool checked);

private:
    double chartX = 100;
    double chartY = 1;
    int chartPos = 0;
    int chartPos_zero = 0;

    double chart_Zadany_scale = 1;
    double chart_PID_scale = 1;
    double chart_Uchyb_scale = 1;

    double chart_Zadany_scale_below = -1;
    double chart_PID_scale_below = -1;
    double chart_Uchyb_scale_below = -1;

    double val_chart_1 = 1;
    double val_chart_1_min= -1;
    double val_chart_2 = 1;
    double val_chart_2_min= -1;
    double val_chart_3 = 1;
    double val_chart_3_min= -1;
    bool tet = true;
    bool remove = 0;
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

