#ifndef DANEPOBIERANE_H
#define DANEPOBIERANE_H

#include <QDialog>

namespace Ui {
class DanePobierane;
}

class DanePobierane : public QDialog
{
    Q_OBJECT

public:
    explicit DanePobierane(QWidget *parent = nullptr);
    ~DanePobierane();
    void UstawienieDostepnosci(QString n);
    void Czyszczenie();

private slots:


    void on_ZatwierdzenieUstawien_accepted();

signals:
    void PrzesylanieDanych(QString adres,int port);
    void BledneDane();

private:
    Ui::DanePobierane *ui;
    QString rola;
};

#endif // DANEPOBIERANE_H
