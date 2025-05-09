/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *serwer;
    QGroupBox *parametry_main;
    QGroupBox *box_arx;
    QLineEdit *arxA_Input;
    QLineEdit *arxB_Input;
    QLineEdit *opoznienie_Input;
    QPushButton *Arx_window_btn;
    QGroupBox *box_pid;
    QLineEdit *PIDwzmocnienie_Input;
    QLineEdit *PIDTi_input;
    QLineEdit *PIDTd_input;
    QLabel *label_PIDwzmocnienie;
    QLabel *label_PIDTi;
    QLabel *label_PIDTd;
    QGroupBox *box_gen;
    QLineEdit *GenAmp_input;
    QLineEdit *GenT_Input;
    QLineEdit *GenFill_Input;
    QLabel *label_GenAmp;
    QLabel *label_GenT;
    QLabel *label_GenFill;
    QGroupBox *box_add;
    QComboBox *genType_Box;
    QLabel *label_genType;
    QLineEdit *interwal_Input;
    QLabel *label_interwal;
    QLineEdit *zaklocenia_Input;
    QPushButton *start_button;
    QPushButton *stop_button;
    QPushButton *reset_button;
    QPushButton *save_button;
    QPushButton *load_button;
    QCheckBox *Tryb_I;
    QLabel *Tryb_label;
    QPushButton *PID_reset_I;
    QToolButton *WyborRoli;
    QCheckBox *trybSieciowy;
    QPushButton *DaneDoPolaczenia;
    QLabel *statusPolaczony;
    QPushButton *btnWlacz;
    QPushButton *test;
    QPushButton *btnWylacz;
    QLabel *LEDdioda;
    QLabel *labelAdres;
    QLabel *labelPort;
    QLabel *wyswietlanyAdres;
    QLabel *wyswietlanyPort;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *layout_wykres1;
    QVBoxLayout *layout_wykres2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1538, 927);
        MainWindow->setMinimumSize(QSize(800, 760));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        serwer = new QGroupBox(centralwidget);
        serwer->setObjectName("serwer");
        serwer->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(serwer->sizePolicy().hasHeightForWidth());
        serwer->setSizePolicy(sizePolicy);
        serwer->setMinimumSize(QSize(350, 770));
        serwer->setMaximumSize(QSize(350, 760));
        QFont font;
        font.setPointSize(21);
        font.setItalic(true);
        serwer->setFont(font);
        parametry_main = new QGroupBox(serwer);
        parametry_main->setObjectName("parametry_main");
        parametry_main->setGeometry(QRect(10, 200, 331, 570));
        sizePolicy.setHeightForWidth(parametry_main->sizePolicy().hasHeightForWidth());
        parametry_main->setSizePolicy(sizePolicy);
        parametry_main->setMinimumSize(QSize(250, 560));
        parametry_main->setMaximumSize(QSize(350, 700));
        QFont font1;
        font1.setPointSize(9);
        font1.setItalic(true);
        parametry_main->setFont(font1);
        parametry_main->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        box_arx = new QGroupBox(parametry_main);
        box_arx->setObjectName("box_arx");
        box_arx->setGeometry(QRect(0, 20, 331, 71));
        arxA_Input = new QLineEdit(box_arx);
        arxA_Input->setObjectName("arxA_Input");
        arxA_Input->setGeometry(QRect(200, 30, 113, 28));
        arxA_Input->setReadOnly(true);
        arxB_Input = new QLineEdit(box_arx);
        arxB_Input->setObjectName("arxB_Input");
        arxB_Input->setGeometry(QRect(200, 70, 113, 28));
        arxB_Input->setReadOnly(true);
        opoznienie_Input = new QLineEdit(box_arx);
        opoznienie_Input->setObjectName("opoznienie_Input");
        opoznienie_Input->setGeometry(QRect(200, 110, 113, 28));
        opoznienie_Input->setReadOnly(true);
        Arx_window_btn = new QPushButton(box_arx);
        Arx_window_btn->setObjectName("Arx_window_btn");
        Arx_window_btn->setGeometry(QRect(30, 20, 101, 41));
        box_pid = new QGroupBox(parametry_main);
        box_pid->setObjectName("box_pid");
        box_pid->setGeometry(QRect(0, 90, 331, 121));
        PIDwzmocnienie_Input = new QLineEdit(box_pid);
        PIDwzmocnienie_Input->setObjectName("PIDwzmocnienie_Input");
        PIDwzmocnienie_Input->setGeometry(QRect(200, 20, 113, 28));
        PIDTi_input = new QLineEdit(box_pid);
        PIDTi_input->setObjectName("PIDTi_input");
        PIDTi_input->setGeometry(QRect(200, 50, 113, 28));
        PIDTd_input = new QLineEdit(box_pid);
        PIDTd_input->setObjectName("PIDTd_input");
        PIDTd_input->setGeometry(QRect(200, 80, 113, 28));
        label_PIDwzmocnienie = new QLabel(box_pid);
        label_PIDwzmocnienie->setObjectName("label_PIDwzmocnienie");
        label_PIDwzmocnienie->setGeometry(QRect(80, 20, 91, 20));
        label_PIDTi = new QLabel(box_pid);
        label_PIDTi->setObjectName("label_PIDTi");
        label_PIDTi->setGeometry(QRect(50, 50, 131, 20));
        label_PIDTd = new QLabel(box_pid);
        label_PIDTd->setObjectName("label_PIDTd");
        label_PIDTd->setGeometry(QRect(30, 80, 161, 20));
        box_gen = new QGroupBox(parametry_main);
        box_gen->setObjectName("box_gen");
        box_gen->setGeometry(QRect(0, 210, 331, 121));
        GenAmp_input = new QLineEdit(box_gen);
        GenAmp_input->setObjectName("GenAmp_input");
        GenAmp_input->setGeometry(QRect(200, 20, 113, 28));
        GenT_Input = new QLineEdit(box_gen);
        GenT_Input->setObjectName("GenT_Input");
        GenT_Input->setGeometry(QRect(200, 50, 113, 28));
        GenFill_Input = new QLineEdit(box_gen);
        GenFill_Input->setObjectName("GenFill_Input");
        GenFill_Input->setGeometry(QRect(200, 80, 113, 28));
        label_GenAmp = new QLabel(box_gen);
        label_GenAmp->setObjectName("label_GenAmp");
        label_GenAmp->setGeometry(QRect(100, 30, 81, 20));
        label_GenT = new QLabel(box_gen);
        label_GenT->setObjectName("label_GenT");
        label_GenT->setGeometry(QRect(140, 60, 21, 20));
        label_GenFill = new QLabel(box_gen);
        label_GenFill->setObjectName("label_GenFill");
        label_GenFill->setGeometry(QRect(90, 90, 91, 20));
        box_add = new QGroupBox(parametry_main);
        box_add->setObjectName("box_add");
        box_add->setGeometry(QRect(0, 330, 331, 111));
        genType_Box = new QComboBox(box_add);
        genType_Box->addItem(QString());
        genType_Box->addItem(QString());
        genType_Box->addItem(QString());
        genType_Box->setObjectName("genType_Box");
        genType_Box->setGeometry(QRect(210, 30, 82, 28));
        genType_Box->setEditable(false);
        label_genType = new QLabel(box_add);
        label_genType->setObjectName("label_genType");
        label_genType->setGeometry(QRect(90, 30, 101, 20));
        interwal_Input = new QLineEdit(box_add);
        interwal_Input->setObjectName("interwal_Input");
        interwal_Input->setGeometry(QRect(190, 70, 113, 28));
        label_interwal = new QLabel(box_add);
        label_interwal->setObjectName("label_interwal");
        label_interwal->setGeometry(QRect(110, 70, 63, 20));
        zaklocenia_Input = new QLineEdit(box_add);
        zaklocenia_Input->setObjectName("zaklocenia_Input");
        zaklocenia_Input->setGeometry(QRect(190, 100, 113, 28));
        zaklocenia_Input->setReadOnly(true);
        start_button = new QPushButton(parametry_main);
        start_button->setObjectName("start_button");
        start_button->setGeometry(QRect(10, 450, 83, 29));
        stop_button = new QPushButton(parametry_main);
        stop_button->setObjectName("stop_button");
        stop_button->setGeometry(QRect(10, 480, 83, 29));
        reset_button = new QPushButton(parametry_main);
        reset_button->setObjectName("reset_button");
        reset_button->setGeometry(QRect(10, 510, 83, 29));
        save_button = new QPushButton(parametry_main);
        save_button->setObjectName("save_button");
        save_button->setEnabled(true);
        save_button->setGeometry(QRect(260, 600, 83, 29));
        load_button = new QPushButton(parametry_main);
        load_button->setObjectName("load_button");
        load_button->setGeometry(QRect(260, 650, 83, 29));
        Tryb_I = new QCheckBox(parametry_main);
        Tryb_I->setObjectName("Tryb_I");
        Tryb_I->setGeometry(QRect(100, 480, 131, 31));
        Tryb_label = new QLabel(parametry_main);
        Tryb_label->setObjectName("Tryb_label");
        Tryb_label->setGeometry(QRect(210, 480, 111, 31));
        PID_reset_I = new QPushButton(parametry_main);
        PID_reset_I->setObjectName("PID_reset_I");
        PID_reset_I->setGeometry(QRect(100, 450, 91, 24));
        WyborRoli = new QToolButton(serwer);
        WyborRoli->setObjectName("WyborRoli");
        WyborRoli->setGeometry(QRect(10, 90, 321, 26));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(WyborRoli->sizePolicy().hasHeightForWidth());
        WyborRoli->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setPointSize(11);
        font2.setItalic(true);
        WyborRoli->setFont(font2);
        trybSieciowy = new QCheckBox(serwer);
        trybSieciowy->setObjectName("trybSieciowy");
        trybSieciowy->setGeometry(QRect(10, 40, 181, 20));
        QFont font3;
        font3.setPointSize(12);
        font3.setItalic(true);
        trybSieciowy->setFont(font3);
        DaneDoPolaczenia = new QPushButton(serwer);
        DaneDoPolaczenia->setObjectName("DaneDoPolaczenia");
        DaneDoPolaczenia->setGeometry(QRect(180, 164, 161, 31));
        QFont font4;
        font4.setPointSize(10);
        font4.setItalic(true);
        DaneDoPolaczenia->setFont(font4);
        statusPolaczony = new QLabel(serwer);
        statusPolaczony->setObjectName("statusPolaczony");
        statusPolaczony->setGeometry(QRect(210, 130, 101, 21));
        statusPolaczony->setFont(font4);
        statusPolaczony->setAlignment(Qt::AlignmentFlag::AlignCenter);
        btnWlacz = new QPushButton(serwer);
        btnWlacz->setObjectName("btnWlacz");
        btnWlacz->setGeometry(QRect(10, 120, 161, 35));
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnWlacz->sizePolicy().hasHeightForWidth());
        btnWlacz->setSizePolicy(sizePolicy2);
        btnWlacz->setMinimumSize(QSize(90, 35));
        QFont font5;
        font5.setPointSize(12);
        font5.setBold(false);
        font5.setItalic(true);
        btnWlacz->setFont(font5);
        test = new QPushButton(serwer);
        test->setObjectName("test");
        test->setGeometry(QRect(10, 60, 75, 24));
        test->setFont(font4);
        btnWylacz = new QPushButton(serwer);
        btnWylacz->setObjectName("btnWylacz");
        btnWylacz->setGeometry(QRect(10, 160, 161, 35));
        sizePolicy2.setHeightForWidth(btnWylacz->sizePolicy().hasHeightForWidth());
        btnWylacz->setSizePolicy(sizePolicy2);
        btnWylacz->setMinimumSize(QSize(90, 35));
        btnWylacz->setFont(font3);
        LEDdioda = new QLabel(serwer);
        LEDdioda->setObjectName("LEDdioda");
        LEDdioda->setGeometry(QRect(290, 35, 21, 21));
        LEDdioda->setFont(font4);
        labelAdres = new QLabel(serwer);
        labelAdres->setObjectName("labelAdres");
        labelAdres->setGeometry(QRect(180, 50, 49, 16));
        labelAdres->setFont(font4);
        labelPort = new QLabel(serwer);
        labelPort->setObjectName("labelPort");
        labelPort->setGeometry(QRect(180, 70, 49, 16));
        labelPort->setFont(font4);
        wyswietlanyAdres = new QLabel(serwer);
        wyswietlanyAdres->setObjectName("wyswietlanyAdres");
        wyswietlanyAdres->setGeometry(QRect(220, 50, 71, 16));
        wyswietlanyAdres->setFont(font4);
        wyswietlanyPort = new QLabel(serwer);
        wyswietlanyPort->setObjectName("wyswietlanyPort");
        wyswietlanyPort->setGeometry(QRect(220, 70, 71, 16));
        wyswietlanyPort->setFont(font4);

        horizontalLayout->addWidget(serwer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        layout_wykres1 = new QVBoxLayout();
        layout_wykres1->setObjectName("layout_wykres1");

        verticalLayout_2->addLayout(layout_wykres1);

        layout_wykres2 = new QVBoxLayout();
        layout_wykres2->setObjectName("layout_wykres2");

        verticalLayout_2->addLayout(layout_wykres2);


        horizontalLayout->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        serwer->setTitle(QCoreApplication::translate("MainWindow", "Symulator UAR", nullptr));
        parametry_main->setTitle(QCoreApplication::translate("MainWindow", "Parametry symulacji", nullptr));
        box_arx->setTitle(QCoreApplication::translate("MainWindow", "ARX", nullptr));
        Arx_window_btn->setText(QCoreApplication::translate("MainWindow", "Arx", nullptr));
        box_pid->setTitle(QCoreApplication::translate("MainWindow", "PID", nullptr));
        label_PIDwzmocnienie->setText(QCoreApplication::translate("MainWindow", "Wzmocnienie", nullptr));
        label_PIDTi->setText(QCoreApplication::translate("MainWindow", "Sta\305\202a ca\305\202kowania Ti", nullptr));
        label_PIDTd->setText(QCoreApplication::translate("MainWindow", "Sta\305\202a r\303\263\305\274niczkowania Td", nullptr));
        box_gen->setTitle(QCoreApplication::translate("MainWindow", "Generator", nullptr));
        label_GenAmp->setText(QCoreApplication::translate("MainWindow", "Amplituda", nullptr));
        label_GenT->setText(QCoreApplication::translate("MainWindow", "T", nullptr));
        label_GenFill->setText(QCoreApplication::translate("MainWindow", "Wype\305\202nienie", nullptr));
        box_add->setTitle(QCoreApplication::translate("MainWindow", "Dodatkowe", nullptr));
        genType_Box->setItemText(0, QCoreApplication::translate("MainWindow", "Skok", nullptr));
        genType_Box->setItemText(1, QCoreApplication::translate("MainWindow", "Sin", nullptr));
        genType_Box->setItemText(2, QCoreApplication::translate("MainWindow", "Square", nullptr));

        label_genType->setText(QCoreApplication::translate("MainWindow", "Typ generatora", nullptr));
        label_interwal->setText(QCoreApplication::translate("MainWindow", "Interwa\305\202 (s)", nullptr));
        start_button->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        stop_button->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        reset_button->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        save_button->setText(QCoreApplication::translate("MainWindow", "Zapisz", nullptr));
        load_button->setText(QCoreApplication::translate("MainWindow", "Wczytaj", nullptr));
        Tryb_I->setText(QCoreApplication::translate("MainWindow", "Tryb Ca\305\202kowania:", nullptr));
        Tryb_label->setText(QString());
        PID_reset_I->setText(QCoreApplication::translate("MainWindow", "Reset Pami\304\231ci", nullptr));
        WyborRoli->setText(QCoreApplication::translate("MainWindow", "Wybierz", nullptr));
        trybSieciowy->setText(QCoreApplication::translate("MainWindow", "Tryb Sieciowy", nullptr));
        DaneDoPolaczenia->setText(QCoreApplication::translate("MainWindow", "Dane", nullptr));
        statusPolaczony->setText(QCoreApplication::translate("MainWindow", "Niepo\305\202\304\205czony", nullptr));
        btnWlacz->setText(QCoreApplication::translate("MainWindow", "W\305\202\304\205cz", nullptr));
        test->setText(QCoreApplication::translate("MainWindow", "Test", nullptr));
        btnWylacz->setText(QCoreApplication::translate("MainWindow", "Wy\305\202\304\205cz", nullptr));
        LEDdioda->setText(QString());
        labelAdres->setText(QCoreApplication::translate("MainWindow", "Adres:", nullptr));
        labelPort->setText(QCoreApplication::translate("MainWindow", "Port:", nullptr));
        wyswietlanyAdres->setText(QString());
        wyswietlanyPort->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
