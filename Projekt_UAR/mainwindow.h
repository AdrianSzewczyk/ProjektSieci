
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include "Symulator.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr,Symulator *sym = nullptr);
    ~MainWindow();

private:
    // Pola do wprowadzania danych
    QLineEdit *arxAInput;
    QLineEdit *arxBInput;
    QLineEdit *pidKInput;
    QLineEdit *pidTiInput;
    QLineEdit *pidTdInput;
    QLineEdit *genStepInput;
    QLineEdit *genSinInput;
    QLineEdit *genSquareInput;

    // Wynik symulacji
    QLabel *simulationResult;

    // Przyciski
    QPushButton *simulateButton;

    // Symulator
    Symulator* symulator;

};

#endif // MAINWINDOW_H

