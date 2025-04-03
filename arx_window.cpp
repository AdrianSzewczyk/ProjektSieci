#include "arx_window.h"
#include "ui_arx_window.h"

ARX_window::ARX_window(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ARX_window)
{
    ui->setupUi(this);

    QDoubleSpinBox *wierszA = new QDoubleSpinBox();
    QDoubleSpinBox *wierszB = new QDoubleSpinBox();
    Dodaj_Spinbox(ui->Wartosci_A_layout,&wartosci_A,wierszA);
    Dodaj_Spinbox(ui->Wartosci_B_layout,&wartosci_B,wierszB);
}

ARX_window::~ARX_window()
{
    delete ui;
}

void ARX_window::Dodaj_Spinbox(QVBoxLayout *layout,QVector<QDoubleSpinBox*> *wartosci, QDoubleSpinBox *box)
{
    //wartosci.push_back(box);
    wartosci->append(box);
    layout->addWidget(box);
    //qDebug()<<wartosci->size();
}

void ARX_window::Usun_Spinbox(QVBoxLayout *layout,QVector<QDoubleSpinBox*> *wartosci)
{
    if(wartosci->size() > 1)
    {
        QDoubleSpinBox *wiersz = wartosci->back();
        layout->removeWidget(wartosci->back());
        wartosci->pop_back();
        delete wiersz;
    }
}

void ARX_window::on_Dodaj_A_clicked()
{
    QDoubleSpinBox *wiersz = new QDoubleSpinBox();
    Dodaj_Spinbox(ui->Wartosci_A_layout,&wartosci_A,wiersz);
}

void ARX_window::on_Usun_A_clicked()
{
    Usun_Spinbox(ui->Wartosci_A_layout,&wartosci_A);
    //qDebug()<<wartosci_A.size();
}


void ARX_window::on_Dodaj_B_clicked()
{
    QDoubleSpinBox *wiersz = new QDoubleSpinBox();
    Dodaj_Spinbox(ui->Wartosci_B_layout,&wartosci_B,wiersz);
}


void ARX_window::on_Usun_B_clicked()
{
    Usun_Spinbox(ui->Wartosci_B_layout,&wartosci_B);
}

