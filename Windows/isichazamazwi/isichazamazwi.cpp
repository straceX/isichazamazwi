#include "isichazamazwi.h"
#include "ui_isichazamazwi.h"

isichazamazwi::isichazamazwi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::isichazamazwi)
{
    ui->setupUi(this);
}

isichazamazwi::~isichazamazwi()
{
    delete ui;
}
