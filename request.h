#ifndef REQUEST_H
#define REQUEST_H

#include "QtNetwork/qnetworkaccessmanager.h"
#include <functional>
class Request : QObject {

public:
    QNetworkAccessManager manager;
    QNetworkReply *reply;

    // void qGet(QString url, std::function<void(QByteArray &data)> readyHandle,
    //           std::function<void(QByteArray &data)> finishedHandle);

    QByteArray qGetSync(QString url);
};

#endif // REQUEST_H
