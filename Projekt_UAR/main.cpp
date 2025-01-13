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
QT_USE_NAMESPACE

    int main(int argc, char *argv[])
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

