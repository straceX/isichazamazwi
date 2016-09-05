#include <QCoreApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>

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
QString send_http_request(QString source){

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
    //QString text = ui->textEdit->toPlainText();
    QString src = ui->txt_source->text();
    qDebug() << "Success-->" <<src;
    QString dest =send_http_request(src);
    parse_http(dest);
    qDebug() << "Success-->" <<dest;




}
