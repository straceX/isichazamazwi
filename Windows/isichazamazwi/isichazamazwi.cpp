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

isichazamazwi::isichazamazwi(QWidget *parent) :
    //QMainWindow(parent,Qt::FramelessWindowHint | Qt::WindowSystemMenuHint),
    ui(new Ui::isichazamazwi)
{
    ui->setupUi(this);
    ui->rbtn_google->setChecked(true);

    //ui->menuTranslator->addAction(tr("&Ask question"),this, SLOT(askQuestion()), tr("Alt+A"));

    ui->menuTranslator->addAction(tr("Exit"),this, SLOT(exit()), tr("Alt+F4"));
    ui->btn_save_it->setVisible(false);
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

QString send_http_request(QString source,int type){

    QString ans;
    //QString src = QString("http://tureng.com/tr/turkce-ingilizce/") + source;
    //create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest req( QUrl(QString("http://ceviri.yandex.com.tr/?text=merhaba&lang=tr-en"))  );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {
        //success
        //qDebug() << "Success" <<reply->readAll();
        ans = reply->readAll();
        delete reply;
    }
    else {
        //failure
        //qDebug() << "Failure" <<reply->errorString();
        ans = "";
        delete reply;
    }
    return ans;
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

       QString src = ui->txt_source->text();

       QString dest =send_http_request(src,type);

       parse_http(dest);

       ui->txt_destination->setText(QString::number(type));
       ui->btn_save_it->setVisible(true);

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
