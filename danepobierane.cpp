#include "danepobierane.h"
#include "ui_danepobierane.h"

DanePobierane::DanePobierane(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DanePobierane)
{
    ui->setupUi(this);
    ui->nrPortu->setRange(0,99999);
}

DanePobierane::~DanePobierane()
{
    delete ui;
}

void DanePobierane::on_ZatwierdzenieUstawien_accepted()
{

    int numerPortu = ui->nrPortu->value();
    QString adres = ui->adresIP->text();
    if(rola=="Serwer"){
        if(numerPortu>0){
            emit PrzesylanieDanych(adres,numerPortu);
        }else{
            emit BledneDane();
        }
    }else if(rola=="Klient"){
        if(numerPortu>0&&!adres.isEmpty()){
            emit PrzesylanieDanych(adres,numerPortu);
        }else{
            emit BledneDane();
        }
    }

    //Czyszczenie();

}
void DanePobierane::UstawienieDostepnosci(QString n){
    rola=n;
    if(n=="Serwer"){
        ui->adresIP->setEnabled(false);
        ui->nrPortu->setEnabled(true);
    }else if(n=="Klient"||n=="Nikt"){
        ui->adresIP->setEnabled(true);
        ui->nrPortu->setEnabled(true);
    }
}

void DanePobierane::Czyszczenie(){
    ui->adresIP->clear();
    ui->nrPortu->clear();
}
