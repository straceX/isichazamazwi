#include "nt_operations.h"

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
