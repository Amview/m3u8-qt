#include "filedownload.h"
#include "QtNetwork/qnetworkreply.h"
#include <QFile>

FileDownload::FileDownload(QObject *parent)
    : QObject{parent}
{}

void FileDownload::download(QString &urlstring) {
    QUrl url(urlstring);
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    qDebug() << reply->error();
    QStringList split = urlstring.split("/");
    qDebug() << "下载路径" << "/Users/hua/Desktop/dir/" + split.last();
    // 连接信号以处理下载进度、完成或错误
    connect(reply, &QNetworkReply::finished, [this, split, reply](){
        qDebug() << "开始下载" << reply->error();
        if (reply->error() == QNetworkReply::NoError)
        {
           saveToFile(reply, "/Users/hua/Desktop/dir/" + split.last());
        }
        reply->deleteLater();
    });
    connect(reply, &QNetworkReply::downloadProgress, this, [](qint64 bytesReceived, qint64 bytesTotal){
        qDebug() << "接受字节" << bytesReceived;
        if (bytesTotal > 0) { // 确保总大小大于0以避免除以0错误
            int progress = (bytesReceived * 100) / bytesTotal;
            qDebug() << "进度" << progress;
        }
    });
}

void FileDownload::saveToFile(QNetworkReply *reply, QString path) {
    qDebug() << "开始保存文件";
    QFile file(path);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(reply->readAll());
        file.close();
        qDebug() << "Downloaded successfully.";
    }
    else
    {
        qDebug() << "Failed to save";
    }
}
