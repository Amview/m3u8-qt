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
    struct Segment
    {
        string url;
        string duration;
    };

    explicit M3u8(QObject *parent = nullptr);

    std::vector<string> readM3u8(string url);

    bool checkIsPlaySource(string url);
    bool checkIsPlaySource(std::vector<string> list);

    std::vector<string> analysePlayList(string url);
    std::vector<string> analysePlayList(std::vector<string> list, Utils::UrlPart urlPart);

    std::vector<string> splitUrl(string url);

public slots:
    void showMessage() {
        // 这里是在主线程中安全地显示消息框
        QMessageBox::information(nullptr, "Information", "This is an information message.");
    }
};

#endif // M3U8_H
