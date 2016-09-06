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
    QMainWindow(parent),
    ui(new Ui::isichazamazwi)
{
    ui->setupUi(this);
    ui->rbtn_google->setChecked(true);
}

isichazamazwi::~isichazamazwi()
{
    delete ui;
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
    QNetworkRequest req( QUrl(QString("https://translate.google.com.tr/?hl=tr#en/tr/Hello"))  );
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




}

