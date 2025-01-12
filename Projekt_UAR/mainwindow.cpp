
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
}

MainWindow::~MainWindow()
{
}
/* STARY KOD
 * #include "mainwindow.h"
#include <QMessageBox>
#include <QtCharts/QChart>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), symulator({-0.4}, {0.6}, 1, false, 1.0, 1.0, 1.0, 1.0, 1, 0.5)
{
    // Inicjalizacja pól wprowadzania danych
    arxAInput = new QLineEdit(this);
    arxBInput = new QLineEdit(this);
    pidKInput = new QLineEdit(this);
    pidTiInput = new QLineEdit(this);
    pidTdInput = new QLineEdit(this);
    genStepInput = new QLineEdit(this);
    genSinInput = new QLineEdit(this);
    genSquareInput = new QLineEdit(this);

    simulationResult = new QLabel("Wynik symulacji: 0", this);

    simulateButton = new QPushButton("Symuluj", this);

    // Inicjalizacja wykresu
    setpointSeries = new QLineSeries();
    setpointSeries->setName("Wartość zadana");

    controlSeries = new QLineSeries();
    controlSeries->setName("Wartość regulowana");

    QChart *chart = new QChart();
    chart->addSeries(setpointSeries);
    chart->addSeries(controlSeries);

    chart->createDefaultAxes();
    chart->setTitle("Wykres wartości zadanej i regulowanej");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    axisX = new QValueAxis();
    axisX->setTitleText("Kroki symulacji");
    axisX->setLabelFormat("%d");
    axisX->setTickCount(11);
    chart->setAxisX(axisX, setpointSeries);
    chart->setAxisX(axisX, controlSeries);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Wartości");
    axisY->setLabelFormat("%.2f");
    chart->setAxisY(axisY, setpointSeries);
    chart->setAxisY(axisY, controlSeries);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Layout
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->addWidget(new QLabel("ARX - Współczynnik A:"), 0, 0);
    gridLayout->addWidget(arxAInput, 0, 1);
    gridLayout->addWidget(new QLabel("ARX - Współczynnik B:"), 1, 0);
    gridLayout->addWidget(arxBInput, 1, 1);
    gridLayout->addWidget(new QLabel("PID - K:"), 2, 0);
    gridLayout->addWidget(pidKInput, 2, 1);
    gridLayout->addWidget(new QLabel("PID - Ti:"), 3, 0);
    gridLayout->addWidget(pidTiInput, 3, 1);
    gridLayout->addWidget(new QLabel("PID - Td:"), 4, 0);
    gridLayout->addWidget(pidTdInput, 4, 1);
    gridLayout->addWidget(new QLabel("Generator - Krok:"), 5, 0);
    gridLayout->addWidget(genStepInput, 5, 1);
    gridLayout->addWidget(new QLabel("Generator - Sinus:"), 6, 0);
    gridLayout->addWidget(genSinInput, 6, 1);
    gridLayout->addWidget(new QLabel("Generator - Prostokąt:"), 7, 0);
    gridLayout->addWidget(genSquareInput, 7, 1);
    gridLayout->addWidget(simulateButton, 8, 0, 1, 2);
    gridLayout->addWidget(simulationResult, 9, 0, 1, 2);
    gridLayout->addWidget(chartView, 10, 0, 1, 2);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(gridLayout);
    setCentralWidget(centralWidget);

    // Podłącz przycisk do slotu
    connect(simulateButton, &QPushButton::clicked, this, &MainWindow::processSimulation);
}

void MainWindow::processSimulation()
{
    try {
        // Pobierz dane z pól wprowadzania
        QString arxAString = arxAInput->text();
        QString arxBString = arxBInput->text();
        QString pidKString = pidKInput->text();
        QString pidTiString = pidTiInput->text();
        QString pidTdString = pidTdInput->text();
        QString genStepString = genStepInput->text();
        QString genSinString = genSinInput->text();
        QString genSquareString = genSquareInput->text();

        // Konwersja danych na odpowiednie typy
        std::vector<double> arxA = { arxAString.toDouble() };
        std::vector<double> arxB = { arxBString.toDouble() };
        double pidK = pidKString.toDouble();
        double pidTi = pidTiString.toDouble();
        double pidTd = pidTdString.toDouble();
        double genStep = genStepString.toDouble();
        double genSin = genSinString.toDouble();
        double genSquare = genSquareString.toDouble();

        // Ustaw dane w symulatorze
        symulator.set_arx(arxA, arxB, 1, false);
        symulator.set_pid(pidK, pidTi, pidTd);
        symulator.set_gen(genStep, genSin, genSquare);

        // Wyczyść wykresy
        setpointSeries->clear();
        controlSeries->clear();

        // Symulacja kroków
        for (int i = 0; i < 100; ++i) {
            double result = symulator.simulate();
            setpointSeries->append(i, 1.0);  // Wartość zadana (przykład)
            controlSeries->append(i, result);
        }

        axisX->setRange(0, 99); // Poprawienie zakresu osi X
        simulationResult->setText(QString("Wynik symulacji: %1").arg(symulator.simulate()));
    } catch (std::exception &e) {
        QMessageBox::critical(this, "Błąd", e.what());
    }
}

MainWindow::~MainWindow()
{
    delete arxAInput;
    delete arxBInput;
    delete pidKInput;
    delete pidTiInput;
    delete pidTdInput;
    delete genStepInput;
    delete genSinInput;
    delete genSquareInput;
    delete simulationResult;
    delete simulateButton;
    delete chartView;
    delete setpointSeries;
    delete controlSeries;
    delete axisX;
}
*/
