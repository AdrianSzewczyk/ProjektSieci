#ifndef ARX_WINDOW_H
#define ARX_WINDOW_H

#include <QDialog>
#include <QDoubleSpinBox>
#include <QVector>
#include <QVBoxLayout>
namespace Ui {
class ARX_window;
}
struct DaneOkno
{
    std::vector<double> wektor_A ={-0.4};
    std::vector<double> wektor_B ={0.6};
    int opoznienie = 1;
    double blad = 0;
};
class ARX_window : public QDialog
{
    Q_OBJECT

public:
    explicit ARX_window(DaneOkno &dane_out,QWidget *parent = nullptr);
    void Dodaj_Spinbox(QVBoxLayout *layout,QVector<QDoubleSpinBox*> *wartosci, QDoubleSpinBox *box);
    void Usun_Spinbox(QVBoxLayout *layout,QVector<QDoubleSpinBox*> *wartosci);
    ~ARX_window();

private slots:
    void on_Dodaj_A_clicked();

    void on_Usun_A_clicked();

    void on_Dodaj_B_clicked();

    void on_Usun_B_clicked();

    void on_ARX_window_finished(int result);

    void on_Zapisz_Dane_btn_clicked();

private:
    Ui::ARX_window *ui;
    DaneOkno *dane;
    QVector<QDoubleSpinBox*> wartosci_A = {};
    QVector<QDoubleSpinBox*> wartosci_B = {};
};

#endif // ARX_WINDOW_H
