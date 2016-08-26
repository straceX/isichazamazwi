#ifndef ISICHAZAMAZWI_H
#define ISICHAZAMAZWI_H

#include <QMainWindow>

namespace Ui {
class isichazamazwi;
}

class isichazamazwi : public QMainWindow
{
    Q_OBJECT

public:
    explicit isichazamazwi(QWidget *parent = 0);
    ~isichazamazwi();

private:
    Ui::isichazamazwi *ui;
};

#endif // ISICHAZAMAZWI_H
