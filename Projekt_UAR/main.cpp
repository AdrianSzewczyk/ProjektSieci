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
#include "Wybor.h"
#include "test_PID_ARX.h"
QT_USE_NAMESPACE

   int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    // Główne okno aplikacji
    Symulator sym;
    MainWindow window(nullptr,&sym);
    window.setWindowTitle("Symulator z wykresami");
    window.resize(1500, 1000);
    window.setWindowState(Qt::WindowMaximized);
    window.show();

    return a.exec();
}

/*int testy() {
   
    TestPID::test_PID_skokJednostkowy();
    TestARX::test_ARX_skokJednostkowy();
    TestGenerator::test_Generator_skokJednostkowy();
    TestGenerator::test_Generator_sinus();
    TestGenerator::test_Generator_sygnalProstokatny();
    

    return 0;
}
*/