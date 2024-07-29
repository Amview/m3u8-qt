#include "utils.h"
#include <iostream>
#include <string>
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#include <sstream>
#include <fstream>
#include <filesystem>
using namespace std;
Utils::Utils(QObject *parent)
    : QObject{parent}
{}

vector<string> Utils::splitStr(string s, string split) {
    std::vector<std::string> tokens;
    size_t start = 0, end = 0;
    while ((end = s.find(split, start)) != std::string::npos) {
            tokens.push_back(s.substr(start, end - start));
            start = end + 1;
        }
    tokens.push_back(s.substr(start));
    return tokens;
}

Utils::UrlPart Utils::analyseUrl(string url) {
    Utils::UrlPart urlPart;
    vector<string> parts = splitStr(url, "/");
    vector<string> temp;
    for (int i = 0; i < parts.size(); ++i) {
        temp.push_back(parts[i]);
        if (i == 2) {
            urlPart.host = accumulate(temp.begin(), temp.end(), urlPart.host);
        }
        if (i == parts.size() - 2) {
            urlPart.urlExcludeLastPart = accumulate(temp.begin(), temp.end(), urlPart.urlExcludeLastPart);
        }
        if (i != parts.size() - 1) {
            temp.push_back("/");
        }
    }
    urlPart.path = accumulate(temp.begin() + 5, temp.end(), urlPart.path);
    // cout << urlPart.host << endl;
    // cout << urlPart.path << endl;
    // cout << urlPart.urlExcludeLastPart << endl;
    return urlPart;

}

void Utils::printVector(vector<string> list) {
    cout << "打印vector" << endl;
    for (const string& s : list) {
        cout << s << endl;
    }
}

void Utils::downloadTsFile(string filePath, string tsUrl) {
    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
    }
    Utils::UrlPart urlPart = analyseUrl(tsUrl);
    httplib::Client cli(urlPart.host);
    auto result = cli.Get(urlPart.path);
    if (result && result->status == 200) {
        file.write(result->body.data(), result->body.size());
        std::cout << "下载完成：" << tsUrl << std::endl;
    } else {
        std::cerr << "Failed to download file. Status code: " << (result ? std::to_string(result->status) : "N/A") << std::endl;
    }
    file.close();
}

void Utils::meargeFile(string dir, string filename) {
    filesystem::path dirPath(dir);
    try {
        if (filesystem::exists(dirPath)) {
            std::vector<filesystem::path> files;
            for (const auto& entry : filesystem::directory_iterator(dirPath)) {
                if (entry.is_regular_file()) {
                    files.push_back(entry.path());
                }
            }
            std::sort(files.begin(), files.end(), [](const filesystem::path& a, const filesystem::path& b) {
                return a.filename() < b.filename();
            });
            for (const filesystem::path &p : files) {
                string s = p.string();
                if (s.substr(s.length() - 5, s.length()) == ".temp") {
                    if (writeFile(dirPath.append(filename), s)) {
                        filesystem::remove(p);
                    }
                }
            }
        }
    } catch (const filesystem::filesystem_error& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}

int Utils::writeFile(string outputPath, string sourceParh) {
    std::ofstream outputFile(outputPath, std::ios::out | std::ios::app);
    std::ifstream file(sourceParh);
    if (!file.is_open()) {
        std::cerr << "Error opening files." << std::endl;
        return 0;
    }
    std::string line;
    while (getline(file, line)) {
        outputFile << line << "\n";
    }
    file.close();
    outputFile.close();
    cout << "合并：" << sourceParh << endl;
    return 1;
}

int Utils::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    // 转换为时间戳（秒）
    return std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
}
