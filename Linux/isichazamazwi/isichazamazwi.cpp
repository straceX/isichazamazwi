#include <QCoreApplication>
#include <QDebug>
#include <QUrl>
#include <QUrlQuery>
#include <QMessageBox>

#include "isichazamazwi.h"
#include "ui_isichazamazwi.h"

#include "nt_operations.h"
#include "db_operations.h"

isichazamazwi::isichazamazwi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::isichazamazwi)
{
    ui->setupUi(this);
    ui->rbtn_google->setChecked(true);
    ui->menuTranslator->addAction(tr("Exit"),this, SLOT(exit()), tr("Alt+F4"));
    ui->menuTranslator->addAction(tr("Offline Mode"),this, SLOT(offline()));
    ui->menuTranslator->addAction(tr("Online Mode"),this, SLOT(online()));
    ui->btn_save_it->setVisible(false);

    trayMenu = new QMenu(this);    
    trayMenu->addAction(tr("Offline Mode"),this, SLOT(offline()));
    trayMenu->addAction(tr("Online Mode"),this, SLOT(online()));
    trayMenu->addAction(tr("Exit"),this, SLOT(exit()));

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon("../../Files/try.png"));
    trayIcon->setContextMenu(trayMenu);

    trayIcon->show();
    trayIcon->showMessage("isichazamazwi", "Dictionary is started!..",QSystemTrayIcon::Information, 2510);    

}

isichazamazwi::~isichazamazwi()
{
    delete ui;
}
void isichazamazwi::exit()
{
    close();
    qApp->quit();
}

void print_message_box(QString text)
{
    QMessageBox Msgbox;
    Msgbox.setText(text);
    Msgbox.setStandardButtons(QMessageBox::Ok);
    Msgbox.exec();
}

void isichazamazwi::offline()
{
    if(!isichazamazwi::offlineMode)
    {
        isichazamazwi::offlineMode = true;
        trayIcon->showMessage("isichazamazwi", "Your dictionary run offline mode!..",QSystemTrayIcon::Information, 2510);
        QWidget::setWindowTitle("isichazamazwi (offline mode)");
    }

}

void isichazamazwi::online()
{
    if(isichazamazwi::offlineMode)
    {
        isichazamazwi::offlineMode = false;
        trayIcon->showMessage("isichazamazwi", "Your dictionary run online mode!..",QSystemTrayIcon::Information, 2510);
        QWidget::setWindowTitle("isichazamazwi");
    }

}

QString parse_http(QString &src)
{
    try {
        src = QString("...");

    } catch (...) {

    }

    return src;
}

void isichazamazwi::on_btn_translate_clicked()
{
    int type;

    if(ui->rbtn_google->isChecked())
        type = 0;
    else if(ui->rbtn_yandex->isChecked())
        type = 1;
    else if (ui->rbtn_bing->isChecked())
        type = 2;
    else
        type = -1;


    QString src = ui->txt_source->text();
    QString dest =send_http_request(src,type);
    parse_http(dest);

    ui->txt_destination->setText(QString::number(type));
    ui->btn_save_it->setVisible(true);
    ui->btn_translate->setVisible(false);


}


void isichazamazwi::on_btn_save_it_clicked()
{
    try {

        db_operations db("isichazamazwi.db");
        db.insert_word(ui->txt_source->text(),ui->txt_destination->text(),2);

    } catch (...) {
        return;
    }

    print_message_box("your word ("+ ui->txt_source->text() + ") added \nlocal dictionary!..");


}

void isichazamazwi::on_rbtn_google_clicked()
{
    ui->btn_save_it->setVisible(false);
    ui->btn_translate->setVisible(true);
}

void isichazamazwi::on_rbtn_yandex_clicked()
{
    ui->btn_save_it->setVisible(false);
    ui->btn_translate->setVisible(true);
}

void isichazamazwi::on_rbtn_bing_clicked()
{
    ui->btn_save_it->setVisible(false);
    ui->btn_translate->setVisible(true);
}
