#include <QCoreApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QMessageBox>

#include "isichazamazwi.h"
#include "ui_isichazamazwi.h"
#include "db_operations.h"
#include "nt_operations.h"

isichazamazwi::isichazamazwi(QWidget *parent) :
    //QMainWindow(parent,Qt::FramelessWindowHint | Qt::WindowSystemMenuHint),
    ui(new Ui::isichazamazwi)
{
    ui->setupUi(this);
        ui->rbtn_google->setChecked(true);
        ui->menuTranslator->addAction(tr("Offline Mode"),this, SLOT(offline()));
        ui->menuTranslator->addAction(tr("Online Mode"),this, SLOT(online()));
        ui->menuTranslator->addAction(tr("Exit"),this, SLOT(exit()), tr("Alt+F4"));
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


        isichazamazwi::setWindowIcon(QIcon("../../Files/try.png"));
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
    return;
}

void isichazamazwi::offline()
{
    if(!isichazamazwi::offlineMode)
    {
        isichazamazwi::offlineMode = true;
        trayIcon->showMessage("isichazamazwi", "Your dictionary run offline mode!..",QSystemTrayIcon::Information, 2510);
        QWidget::setWindowTitle("isichazamazwi (offline mode)");
        return;
    }

}

void isichazamazwi::online()
{
    if(isichazamazwi::offlineMode)
    {
        isichazamazwi::offlineMode = false;
        trayIcon->showMessage("isichazamazwi", "Your dictionary run online mode!..",QSystemTrayIcon::Information, 2510);
        QWidget::setWindowTitle("isichazamazwi");
        return;
    }

}

QString parse_http(QString &src)
{
    src = QString("...");
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

        if(ui->txt_source->text().isEmpty() || ui->txt_source->text().length() < 2)
        {
            print_message_box("Please insert word to translate");
        }
        else
        {
            QString src = ui->txt_source->text();
            QRegExp re("\\b([a-zA-Z]+[a-z]*)\\b");

            if(!re.exactMatch(src))
            {
                print_message_box("Your word include non-alphanumeric characters!");
                return;
            }
            else
            {

                QString dest =send_http_request(src,type);
                QString tmp = parse_http(dest);

                ui->txt_destination->setText(tmp);
                ui->btn_save_it->setVisible(true);
                ui->btn_translate->setVisible(false);
                return;
            }
        }

}

void isichazamazwi::on_btn_save_it_clicked()
{
    try {

        db_operations db("isichazamazwi.db");
        db.insert_word(ui->txt_source->text(),ui->txt_destination->text(),2);

    } catch (...) {
        return;
    }
    QMessageBox Msgbox;
    Msgbox.setText("your word ("+ ui->txt_source->text() + ") added \nlocal dictionary!..");
    Msgbox.setStandardButtons(QMessageBox::Ok);
    Msgbox.exec();
}

void isichazamazwi::on_rbtn_google_clicked()
{
    ui->btn_save_it->setVisible(false);
}

void isichazamazwi::on_rbtn_yandex_clicked()
{
    ui->btn_save_it->setVisible(false);
}

void isichazamazwi::on_rbtn_bing_clicked()
{
    ui->btn_save_it->setVisible(false);
}
void isichazamazwi::on_txt_source_textChanged(const QString &arg1)
{
    ui->txt_destination->clear();
    ui->btn_translate->setVisible(true);
    ui->btn_save_it->setVisible(false);
    return;
}
