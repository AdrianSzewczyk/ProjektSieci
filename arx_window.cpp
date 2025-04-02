#include "arx_window.h"
#include "ui_arx_window.h"

ARX_window::ARX_window(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ARX_window)
{
    ui->setupUi(this);
}

ARX_window::~ARX_window()
{
    delete ui;
}
