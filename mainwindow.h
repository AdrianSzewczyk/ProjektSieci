
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
    ~MainWindow();
    void ustawieniePonowneARX();

protected:
    void closeEvent(QCloseEvent* event) override{poprawneWylaczenie=true;event->accept();}
    //siec.WyslijWiadomoscDoSerwera(-1,StanSymulacji::Stop,0,0,0);}
    void ustawienieWykresow();
    void ustawienieWykresowSerwer();
    void usuniecieWykresow();
    void ponowneUstawienieWykresow();
    void resetARX();
    void resetStatusuPortuAdresu();
    void wyswietlenieStatusuPortuAdresu();
    void ustawienieWartosciGui();
    void ustawienieLayoutowWykresow();
private slots:

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
    //void clientDataReceived(QString message);

    void on_WyborRoli_clicked();



    void on_WyborRoli_triggered(QAction *arg1);




    //Sieć Klient
    void siec_connected();
    void siec_disconnected();
    void siec_errorOccurred(QAbstractSocket::SocketError);
    void on_DaneDoPolaczenia_clicked();
    void PrzypisanieAdresuIportu(QString a,quint16 p);
    void BledneDane();

    void WysylanieRamki();
    void DaneSymulacjiOdSerwera(int n,double w);
    void ObliczeniaObiektu(int nrRam,StanSymulacji s,double i, double w,double wZ);


    //test
    void setDaneSymulatora();


    void on_btnWylacz_clicked();
    void on_trybSieciowy_clicked(bool checked);

signals:
    void wracamyTrybSieciowy(bool ch);
    void rozlacz();
    void symuluj();

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
    double val_chart_4 = 1;
    double val_chart_4_min= -1;
    bool tet = true;
    bool remove = 0;
    QLineSeries *kopiaZadana=nullptr;
    QLineSeries *seriesZ=nullptr;
    QLineSeries *seriesR=nullptr;
    QLineSeries *seriesU=nullptr;
    QLineSeries *seriesP=nullptr;
    QLineSeries *seriesI=nullptr;
    QLineSeries *seriesD=nullptr;
    QLineSeries *seriesSterowanie=nullptr;

    QChart *chart=nullptr;
    QChart *chart1=nullptr;
    QChart *chart2=nullptr;

    QChartView *chartView=nullptr;
    QChartView *chartView1=nullptr;
    QChartView *chartView2=nullptr;
    // Symulator
    DaneOkno dane;
    Symulator* symulator=nullptr;
    Symulator* symSiec=nullptr;
    Symulator* symWzorcowy=nullptr;
    Symulator* kopia=nullptr;
    QTimer *timer = nullptr;
    ARX_window *okno=nullptr;
    Ui::MainWindow *ui;
    //Sieć
    TCPserwer* serwer=nullptr;
    bool serwerWlaczony;
     //QDialog
    QMenu* menu;
    QString wybor;
    bool serwerPołączony;

    double wartoscRegulatora=0.0;



    //Sieć Klient
    ZarzadzanieSiec siec;
    void setZarzadzanieSiec();
    bool klientPołączony;
    DanePobierane* danePobierane=nullptr;
    //QPointF punkty[55];
    QString adres="127.0.0.1";
    quint16 port=12345;
    bool SerwerJuzWystartowal;
    bool klikniete;
    int numerRamki=0;
    double wartoscReg=0.0;
    double wartoscZadana=0.0;
    StanSymulacji st;
    double intCzas;
    double wartoscSterujaca=0.0;
    model_ARX* arx=nullptr;
    model_ARX* kopiaARX;
    double wartoscWyjscia;
    bool testKlikniety;
    int nieodebraneWiadomosci;
    bool czyTrybSieciowy=false;
    bool poprawneWylaczenie=false;

    QTimer* timerSieciowy=nullptr;


    bool ProbnyWykres=false;
    bool wykresSchowany=false;

};

#endif // MAINWINDOW_H

