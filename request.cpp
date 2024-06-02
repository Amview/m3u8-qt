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

// QByteArray Request::qGetSync(QString url) {
//     QUrl qurl(url);
//     QNetworkRequest request;
//     QNetworkAccessManager manager;
//     request.setUrl(qurl);
//     QNetworkReply *reply = manager.get(request);
//     QEventLoop eventLoop;
//     QAbstractSocket::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
//     eventLoop.exec(QEventLoop::ExcludeUserInputEvents);

//     if (reply != Q_NULLPTR) {
//         reply->deleteLater();
//     }
//     qDebug() << reply->error();
//     if (reply->error() == QNetworkReply::NoError) {
//         return reply->readAll();
//     }
//     return NULL;
// }

// void Request::downloadFile() {
//     // qDebug() << "Downloaded";
//     // // std::async(std::launch::async, [this]() {
//     // qDebug() << this->m3u8->playUrls;
//     // for (int i = 0; i < this->m3u8->playUrls.size(); ++i) {
//     //     QString localFilePath = "/Users/hua/Desktop/dir/" + QString::number(i) + ".ts";
//     //     // qDebug() << "文件路径\n"<<localFilePath;
//     //     qDebug() << "下载地址" <<this->m3u8->baseUrl + "/" + this->m3u8->playUrls[i];
//     //                                                               // continue;
//     //                                                               QUrl qurl(this->m3u8->baseUrl + "/" + this->m3u8->playUrls[i]);
//     //     request.setUrl(qurl);
//     //     if (reply != Q_NULLPTR) {
//     //         reply->deleteLater();
//     //     }
//     //     reply = manager.get(request);
//     //     qDebug() << reply->error();
//     //     qDebug() << "start get";
//     //     QObject::connect(reply, &QNetworkReply::finished, this, &MainWindow::saveFile);
//     // }
//     // // });
// }

// void MainWindow::saveFile() {
//     // qDebug() << localFilePath;
//     // QFile file(localFilePath);
//     // qDebug() << "下载文件";
//     // if (file.open(QIODevice::WriteOnly)) {
//     //     file.write(reply->readAll());
//     //     file.close();
//     //     qDebug() << "Downloaded and saved successfully!";
//     // } else {
//     //     qDebug() << "Failed to open local file for writing.";
//     // }
//     // reply->deleteLater();
// }



