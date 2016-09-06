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

    void on_txt_source_cursorPositionChanged(int arg1, int arg2);

    void on_txt_source_textEdited(const QString &arg1);

private:
    Ui::isichazamazwi *ui;
};

#endif // ISICHAZAMAZWI_H
