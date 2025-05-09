/********************************************************************************
** Form generated from reading UI file 'arx_window.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARX_WINDOW_H
#define UI_ARX_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ARX_window
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *Wartosci_A_layout;
    QVBoxLayout *Wartosci_B_layout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *Dodaj_A;
    QPushButton *Usun_A;
    QPushButton *Dodaj_B;
    QPushButton *Usun_B;
    QHBoxLayout *horizontalLayout_4;
    QSpinBox *Opoznienie_Box;
    QLabel *label_4;
    QDoubleSpinBox *Zaklocenia_Box;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *Zapisz_Dane_btn;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ARX_window)
    {
        if (ARX_window->objectName().isEmpty())
            ARX_window->setObjectName("ARX_window");
        ARX_window->resize(358, 141);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ARX_window->sizePolicy().hasHeightForWidth());
        ARX_window->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(ARX_window);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_2 = new QLabel(ARX_window);
        label_2->setObjectName("label_2");

        horizontalLayout_3->addWidget(label_2);

        label = new QLabel(ARX_window);
        label->setObjectName("label");

        horizontalLayout_3->addWidget(label);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
        horizontalLayout->setContentsMargins(0, -1, -1, -1);
        Wartosci_A_layout = new QVBoxLayout();
        Wartosci_A_layout->setObjectName("Wartosci_A_layout");

        horizontalLayout->addLayout(Wartosci_A_layout);

        Wartosci_B_layout = new QVBoxLayout();
        Wartosci_B_layout->setObjectName("Wartosci_B_layout");

        horizontalLayout->addLayout(Wartosci_B_layout);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        Dodaj_A = new QPushButton(ARX_window);
        Dodaj_A->setObjectName("Dodaj_A");

        horizontalLayout_2->addWidget(Dodaj_A);

        Usun_A = new QPushButton(ARX_window);
        Usun_A->setObjectName("Usun_A");

        horizontalLayout_2->addWidget(Usun_A);

        Dodaj_B = new QPushButton(ARX_window);
        Dodaj_B->setObjectName("Dodaj_B");

        horizontalLayout_2->addWidget(Dodaj_B);

        Usun_B = new QPushButton(ARX_window);
        Usun_B->setObjectName("Usun_B");

        horizontalLayout_2->addWidget(Usun_B);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        Opoznienie_Box = new QSpinBox(ARX_window);
        Opoznienie_Box->setObjectName("Opoznienie_Box");
        Opoznienie_Box->setMinimum(1);

        horizontalLayout_4->addWidget(Opoznienie_Box);

        label_4 = new QLabel(ARX_window);
        label_4->setObjectName("label_4");

        horizontalLayout_4->addWidget(label_4);

        Zaklocenia_Box = new QDoubleSpinBox(ARX_window);
        Zaklocenia_Box->setObjectName("Zaklocenia_Box");
        Zaklocenia_Box->setSingleStep(0.010000000000000);

        horizontalLayout_4->addWidget(Zaklocenia_Box);

        label_3 = new QLabel(ARX_window);
        label_3->setObjectName("label_3");

        horizontalLayout_4->addWidget(label_3);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        Zapisz_Dane_btn = new QPushButton(ARX_window);
        Zapisz_Dane_btn->setObjectName("Zapisz_Dane_btn");

        horizontalLayout_6->addWidget(Zapisz_Dane_btn);

        buttonBox = new QDialogButtonBox(ARX_window);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Close);

        horizontalLayout_6->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 20);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 1);

        retranslateUi(ARX_window);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, ARX_window, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, ARX_window, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(ARX_window);
    } // setupUi

    void retranslateUi(QDialog *ARX_window)
    {
        ARX_window->setWindowTitle(QCoreApplication::translate("ARX_window", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("ARX_window", "Parametry A", nullptr));
        label->setText(QCoreApplication::translate("ARX_window", "Parametry B", nullptr));
        Dodaj_A->setText(QCoreApplication::translate("ARX_window", "Dodaj A", nullptr));
        Usun_A->setText(QCoreApplication::translate("ARX_window", "Usu\305\204", nullptr));
        Dodaj_B->setText(QCoreApplication::translate("ARX_window", "Dodaj B", nullptr));
        Usun_B->setText(QCoreApplication::translate("ARX_window", "Usu\305\204", nullptr));
        label_4->setText(QCoreApplication::translate("ARX_window", "Op\303\263\305\274nienie", nullptr));
        label_3->setText(QCoreApplication::translate("ARX_window", "Zak\305\202\303\263cenia", nullptr));
        Zapisz_Dane_btn->setText(QCoreApplication::translate("ARX_window", "Zapisz", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ARX_window: public Ui_ARX_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARX_WINDOW_H
