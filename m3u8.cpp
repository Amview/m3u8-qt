#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "QtWidgets/qapplication.h"
#include "m3u8.h"
#include "utils.h"
#include <iostream>
#include <QMessageBox>
#include <QMetaObject>
#include "httplib.h"
using namespace std;
M3u8::M3u8(QObject *parent)
    : QObject{parent}
{
    this->parent = parent;
}

std::vector<string> M3u8::readM3u8(string url) {
    Utils::UrlPart urlPart = Utils::analyseUrl(url);
    httplib::Client cli(urlPart.host);
    httplib::Result res = cli.Get(urlPart.path);
    std::cout << res->status << std::endl;
    std::vector<string> lines;
    if (res && res->status == 200) {
        lines = Utils::splitStr(res->body, "\n");
    }
    return lines;
}

std::vector<string> M3u8::analysePlayList(std::vector<string> list, Utils::UrlPart urlPart) {
    std::vector<string> playList;
    for (int i = 0; i < list.size(); ++i) {
        if (!list[i].empty() && list[i].substr(0, 1) != "#") {
            // 以/开头
            if (list[i].substr(0, 1) == "/") {
                playList.push_back(urlPart.host + list[i]);
            } else {
                playList.push_back(urlPart.urlExcludeLastPart +  "/" + list[i]);
            }
        }
    }
    return playList;
}

std::vector<string> M3u8::analysePlayList(string url) {
    std::vector<string> items = readM3u8(url);
    Utils::UrlPart urlPart = Utils::analyseUrl(url);
    return analysePlayList(items, urlPart);
}

bool M3u8::checkIsPlaySource(string url) {
    std::vector<string> list = readM3u8(url);
    return checkIsPlaySource(list);
}

bool M3u8::checkIsPlaySource(std::vector<string> list) {
    for(const string& s : list) {
        if (s.find("#EXT-X-STREAM-INF") != string::npos) {
            return true;
        }
    }
    return false;
}