#ifndef M3U8_H
#define M3U8_H
#include "QtNetwork/qnetworkaccessmanager.h"
#include "request.h"
#define EXT_X_STREAM_INF "#EXT-X-STREAM-INF"
#define EXTM3U "#EXTM3U"
#define EXTINF "#EXTINF"

#include <QString>
#include <QStringList>
class M3u8 {

public:
    QString url;
    QString baseUrl;
    QNetworkAccessManager manager;
    QNetworkReply *reply;
    Request request;

    void analysisM3u8();
    bool checkIsBack();
    void checkPlaySource();
    int countUrls();

    // 备份源地址

    QStringList playUrls;
    QStringList dataList;
    QByteArray data;

    bool isBackUrl;
    // 是否是备份源
    bool isBack;
    M3u8(QString &url);
    ~M3u8();
};

#endif // M3U8_H

