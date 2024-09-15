#ifndef M3U8_H
#define M3U8_H

#include <QObject>
#include <QMessageBox>
#include "utils.h"
using namespace std;
class M3u8 : public QObject
{
    Q_OBJECT
public:
    QObject *parent;

    explicit M3u8(QObject *parent = nullptr);

    std::vector<string> readM3u8(const string& url);

    bool checkIsPlaySource(const string& url);
    bool checkIsPlaySource(const std::vector<string>& list);

    std::vector<string> analysePlayList(const string& url);
    std::vector<string> analysePlayList(const std::vector<string>& list, const Utils::UrlPart& urlPart);

    std::vector<string> splitUrl(const string& url);

signals:
    void occurError(const string& text);
};

#endif // M3U8_H
