#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "qapplication.h"
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

std::vector<string> M3u8::readM3u8(const string& url) {
    Utils::UrlPart urlPart = Utils::analyseUrl(url);
    std::vector<string> lines;
    httplib::Client cli(urlPart.host);
    httplib::Result res = cli.Get(urlPart.path);
    if (res && res->status == 200) {
        lines = Utils::splitStr(res->body, "\n");
    } else {
        emit occurError(httplib::to_string(res.error()));
    }
    return lines;
}

std::vector<string> M3u8::analysePlayList(const std::vector<string>& list, const Utils::UrlPart& urlPart) {
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

std::vector<string> M3u8::analysePlayList(const string& url) {
    std::vector<string> items = readM3u8(url);
    Utils::UrlPart urlPart = Utils::analyseUrl(url);
    return analysePlayList(items, urlPart);
}

bool M3u8::checkIsPlaySource(const string& url) {
    std::vector<string> list = readM3u8(url);
    return checkIsPlaySource(list);
}

bool M3u8::checkIsPlaySource(const std::vector<string>& list) {
    for(const string& s : list) {
        if (s.find("#EXT-X-STREAM-INF") != string::npos) {
            return true;
        }
    }
    return false;
}