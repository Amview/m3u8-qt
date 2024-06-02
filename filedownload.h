#ifndef FILEDOWNLOAD_H
#define FILEDOWNLOAD_H

#include "QtNetwork/qnetworkaccessmanager.h"
#include <QObject>

class FileDownload : public QObject
{
    Q_OBJECT
public:
    explicit FileDownload(QObject *parent = nullptr);

    // QNetworkAccessManager manager;
    // QNetworkReply *reply;

    void download(QString &url);

    void saveToFile(QNetworkReply *reply, QString path);
};

#endif // FILEDOWNLOAD_H
