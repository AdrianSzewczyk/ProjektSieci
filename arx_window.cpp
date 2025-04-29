#include "arx_window.h"
#include "ui_arx_window.h"

ARX_window::ARX_window(DaneOkno &dane_out,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ARX_window),dane(&dane_out)
{
    ui->setupUi(this);
    connect(ui->Zapisz_Dane_btn,SIGNAL(clicked(bool)),parent,SLOT(wczytaj_dane_okno()));
    /* QDoubleSpinBox *wierszA = new QDoubleSpinBox();
    QDoubleSpinBox *wierszB = new QDoubleSpinBox();
    wierszA->setMinimum(-99.9);
    wierszA->setValue(-0.4);
    wierszB->setValue(0.6);
*/
    foreach (double A, dane->wektor_A)
    {
        QDoubleSpinBox *w = new QDoubleSpinBox();
        w->setMinimum(-99.9);
        w->setValue(A);
        Dodaj_Spinbox(ui->Wartosci_A_layout,&wartosci_A,w);
    }
    foreach (double B, dane->wektor_B)
    {
        QDoubleSpinBox *w = new QDoubleSpinBox();
        w->setMinimum(-99.9);
        w->setValue(B);
        Dodaj_Spinbox(ui->Wartosci_B_layout,&wartosci_B,w);
    }
    ui->Opoznienie_Box->setValue(dane->opoznienie);
    ui->Zaklocenia_Box->setValue(dane->blad);
    //Dodaj_Spinbox(ui->Wartosci_A_layout,&wartosci_A,wierszA);
    //Dodaj_Spinbox(ui->Wartosci_B_layout,&wartosci_B,wierszB);
}

ARX_window::~ARX_window()
{
    delete ui;
}

void ARX_window::Dodaj_Spinbox(QVBoxLayout *layout,QVector<QDoubleSpinBox*> *wartosci, QDoubleSpinBox *box)
{
    //wartosci.push_back(box);
    box->setMaximum(99.9);
    box->setMinimum(-99.9);
    box->setSingleStep(0.1);
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


void ARX_window::on_ARX_window_finished(int result)
{
    Q_UNUSED(result);
    deleteLater();
}

void ARX_window::on_Zapisz_Dane_btn_clicked()
{
    if(dane != nullptr)
    {
        dane->wektor_A = {};
        foreach (QDoubleSpinBox *wart_A, wartosci_A)
        {
            dane->wektor_A.push_back(wart_A->value());
        }
        dane->wektor_B = {};
        foreach (QDoubleSpinBox *wart_B, wartosci_B)
        {
            dane->wektor_B.push_back(wart_B->value());
        }
        dane->blad = ui->Zaklocenia_Box->value();
        dane->opoznienie = ui->Opoznienie_Box->value();
    }
}
