#ifndef NT_OPERATIONS_H
#define NT_OPERATIONS_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

QString send_http_request(QString source,int type);

#endif // NT_OPERATIONS_H
