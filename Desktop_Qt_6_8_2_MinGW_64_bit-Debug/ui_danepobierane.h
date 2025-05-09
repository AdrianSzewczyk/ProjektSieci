/********************************************************************************
** Form generated from reading UI file 'danepobierane.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DANEPOBIERANE_H
#define UI_DANEPOBIERANE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_DanePobierane
{
public:
    QDialogButtonBox *ZatwierdzenieUstawien;
    QLineEdit *adresIP;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *nrPortu;

    void setupUi(QDialog *DanePobierane)
    {
        if (DanePobierane->objectName().isEmpty())
            DanePobierane->setObjectName("DanePobierane");
        DanePobierane->resize(324, 229);
        ZatwierdzenieUstawien = new QDialogButtonBox(DanePobierane);
        ZatwierdzenieUstawien->setObjectName("ZatwierdzenieUstawien");
        ZatwierdzenieUstawien->setGeometry(QRect(-90, 170, 341, 32));
        ZatwierdzenieUstawien->setOrientation(Qt::Orientation::Horizontal);
        ZatwierdzenieUstawien->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        adresIP = new QLineEdit(DanePobierane);
        adresIP->setObjectName("adresIP");
        adresIP->setGeometry(QRect(170, 40, 113, 26));
        label = new QLabel(DanePobierane);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 40, 91, 20));
        QFont font;
        font.setPointSize(12);
        font.setItalic(true);
        label->setFont(font);
        label_2 = new QLabel(DanePobierane);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 100, 131, 20));
        label_2->setFont(font);
        nrPortu = new QSpinBox(DanePobierane);
        nrPortu->setObjectName("nrPortu");
        nrPortu->setGeometry(QRect(200, 100, 81, 26));

        retranslateUi(DanePobierane);
        QObject::connect(ZatwierdzenieUstawien, &QDialogButtonBox::accepted, DanePobierane, qOverload<>(&QDialog::accept));
        QObject::connect(ZatwierdzenieUstawien, &QDialogButtonBox::rejected, DanePobierane, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(DanePobierane);
    } // setupUi

    void retranslateUi(QDialog *DanePobierane)
    {
        DanePobierane->setWindowTitle(QCoreApplication::translate("DanePobierane", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("DanePobierane", "Adres IP:", nullptr));
        label_2->setText(QCoreApplication::translate("DanePobierane", "Numer Portu:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DanePobierane: public Ui_DanePobierane {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DANEPOBIERANE_H
