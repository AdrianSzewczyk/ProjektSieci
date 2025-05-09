
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
#include "arx_window.h"
#include "TCPserwer.h"
#include "ZarzadzanieSiec.h"
#include "danepobierane.h"

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
    void ustawienieWartosci();
    ~MainWindow();
    void ustawieniePonowneARX();

protected:
    void closeEvent(QCloseEvent* event) override{poprawneWylaczenie=true;event->accept();
    siec.WyslijWiadomoscDoSerwera(-1,StanSymulacji::Stop,0,0);}
    void ustawienieWykresow();
    void ustawienieWykresowSerwer();
    void usuniecieWykresow();
    void usuniecieWykresowSerwer();
private slots:


    void symulacjaSerwer(double warR,double warS);
    void simulationProgress();
    void on_reset_button_clicked();

    void on_start_button_clicked();

    void on_stop_button_clicked();

    void on_PIDwzmocnienie_Input_editingFinished();

    void on_PIDTi_input_editingFinished();

    void on_PIDTd_input_editingFinished();

    void on_GenAmp_input_editingFinished();

    void on_GenT_Input_editingFinished();

    void on_GenFill_Input_editingFinished();

    void on_genType_Box_currentIndexChanged(int index);

    void on_interwal_Input_editingFinished();

    void on_Tryb_I_toggled(bool checked);

    void on_PID_reset_I_clicked();

    void on_Arx_window_btn_clicked();

    void wczytaj_dane_okno();



    //Sieć
    void on_btnWlacz_clicked();
    void on_NewClientConnected();
    void clientDisconnected();
    void clientDataReceived(QString message);

    void on_WyborRoli_clicked();



    void on_WyborRoli_triggered(QAction *arg1);




    //Sieć Klient
    void siec_connected();
    void siec_disconnected();
    void siec_stateChanged(QAbstractSocket::SocketState);
    void siec_errorOccurred(QAbstractSocket::SocketError);
    void siec_dataReady(QByteArray data);

    void on_DaneDoPolaczenia_clicked();
    void PrzypisanieAdresuIportu(QString a,quint16 p);
    void BledneDane();

    void WysylanieRamki();
    void DaneSymulacjiOdSerwera(int n,double w);
    void ObliczeniaObiektu(int nrRam,StanSymulacji s,double i, double w);


    //test
    void FunkcjaSprawdzenie();
    void setDaneSymulatora();

    void on_test_clicked();
    void UstawienieDanychTestowych();

    void on_btnWylacz_clicked();
    void on_trybSieciowy_clicked(bool checked);

signals:
    void wracamyTrybSieciowy(bool ch);
    void rozlacz();

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

    QChartView *chartView;
    QChartView *chartView1;
    QChartView *chartView2;
    // Symulator
    DaneOkno dane;
    Symulator* symulator;
    Symulator* symSiec;
    Symulator* symWzorcowy;
    Symulator* kopia;
    QTimer *timer = nullptr;
    QTimer *timerSerwer=nullptr;
    ARX_window *okno;
    Ui::MainWindow *ui;

    //Sieć
    TCPserwer* serwer;
    bool serwerWlaczony;
     //QDialog
    QMenu* menu;
    QString wybor;
    bool serwerPołączony;



    //Sieć Klient
    ZarzadzanieSiec siec;
    void setZarzadzanieSiec();
    bool klientPołączony;
    DanePobierane* danePobierane;

    QString adres;
    quint16 port;
    bool SerwerJuzWystartowal;
    bool klikniete;
    int numerRamki;
    double wartoscReg;
    StanSymulacji st;
    double intCzas;
    double wartoscSterujaca;
    model_ARX* arx;
    model_ARX* kopiaARX;
    double wartoscWyjscia;
    bool testKlikniety;
    int nieodebraneWiadomosci;
    bool czyTrybSieciowy=false;
    bool poprawneWylaczenie=false;

};

#endif // MAINWINDOW_H

