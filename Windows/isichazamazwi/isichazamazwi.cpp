#include "isichazamazwi.h"
#include "ui_isichazamazwi.h"

isichazamazwi::isichazamazwi(QWidget *parent) :
    QMainWindow(parent,Qt::FramelessWindowHint | Qt::WindowSystemMenuHint),
    ui(new Ui::isichazamazwi)
{
    ui->setupUi(this);
}

isichazamazwi::~isichazamazwi()
{
    delete ui;
}

