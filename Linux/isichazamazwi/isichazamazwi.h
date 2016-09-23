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

private slots:
    void on_btn_translate_clicked();
    void on_btn_save_it_clicked();
    void exit();
    void offline();
    void on_rbtn_google_clicked();

    void on_rbtn_yandex_clicked();

    void on_rbtn_bing_clicked();

private:
    Ui::isichazamazwi *ui;
    bool offlineMode= false;
};

#endif // ISICHAZAMAZWI_H
