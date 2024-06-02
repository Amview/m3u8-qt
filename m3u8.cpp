#include "m3u8.h"
#include "QtCore/qeventloop.h"
#include "QtNetwork/qnetworkreply.h"
#include "QObject"
#include "request.h"
#include "iostream"
#include <future>
#include <thread>
M3u8::M3u8(QString &url) {
    this->url = url;
    QStringList list = url.split("/");
    list.removeAt(list.size() - 1);
    this->baseUrl = list.join("/");
    qDebug() << this->baseUrl;
    this->analysisM3u8();
    this->checkPlaySource();
}
M3u8::~M3u8() {

}

int fun (int i) {
    std::cout << "I'm fun" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return i;
}

void analysisM3u8_1(QString &url) {

}

void M3u8::analysisM3u8() {
    QUrl qurl(url);
    QNetworkRequest request;
    QNetworkAccessManager manager;
    request.setUrl(qurl);
    QNetworkReply *reply = manager.get(request);
    QEventLoop eventLoop;
    QAbstractSocket::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    data = reply->readAll();
    qDebug() << reply->error();
    // 清理资源
    reply->deleteLater();
    reply = nullptr;
    dataList = QString::fromUtf8(data).split("\n");
}

bool M3u8::checkIsBack() {
    for (int i = 0; i < dataList.size(); i++) {
        QString s = dataList.at(i);
        // qDebug() << s;
        if (s.contains("#EXT-X-STREAM-INF")) {
            return true;
        }
    }
    return false;
}

int M3u8::countUrls() {
    int count = 0;
    for (int i = 0; i < dataList.size(); ++i) {
        if (!dataList[i].trimmed().startsWith("#")) {
            count++;
        }
    }
    return count;
}

void M3u8::checkPlaySource() {
    // qDebug() << data;
    // qDebug() << "1" <<dataList;
    for (int i = 0; i < dataList.size(); ++i) {
        if (!dataList[i].trimmed().startsWith("#")) {
            QString item = dataList[i];
            if (!item.isEmpty()) {
                playUrls.append(item);
            }
        }
    }
}
