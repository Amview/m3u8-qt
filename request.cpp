#include "request.h"
#include "QtCore/qeventloop.h"
#include "QtNetwork/qnetworkreply.h"
#include "QtNetwork/qnetworkrequest.h"


// void Request::qGet(QString url, std::function<void(QByteArray &data)> readyHandle,
//                    std::function<void(QByteArray &data)> finishedHandle) {
//     QUrl qurl(url);
//     QNetworkRequest request;
//     request.setUrl(qurl);
//     if (reply != Q_NULLPTR) {
//         reply->deleteLater();
//     }
//     reply = manager.get(request);
//     qDebug() << "start get";
//     QObject::connect(reply, &QNetworkReply::readyRead, [=](){
//         qDebug() << reply->error();;
//         // readyHandle(reply->readAll());
//     });
//     QObject::connect(reply, &QNetworkReply::finished, [=](){
//         qDebug() << reply->error();;
//         finishedHandle(reply->readAll());
//     });
// }

QByteArray Request::qGetSync(QString url) {
    QUrl qurl(url);
    QNetworkRequest request;
    QNetworkAccessManager manager;
    request.setUrl(qurl);
    QNetworkReply *reply = manager.get(request);
    QEventLoop eventLoop;
    QAbstractSocket::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);

    if (reply != Q_NULLPTR) {
        reply->deleteLater();
    }
    qDebug() << reply->error();
    if (reply->error() == QNetworkReply::NoError) {
        return reply->readAll();
    }
    return NULL;
}


