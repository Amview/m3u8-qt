#ifndef UTILS_H
#define UTILS_H
#include <QObject>

using namespace std;
class Utils : public QObject
{
    Q_OBJECT
public:
    struct UrlPart
    {
        string host;
        string path;
        string urlExcludeLastPart;
    };

    explicit Utils(QObject *parent = nullptr);
    static vector<string> splitStr(string s, string split);
    static UrlPart analyseUrl(string url);
    static void printVector(vector<string> list);
    static void downloadTsFile(string filePath, string tsUrl);
    static void meargeFile(string dir, string filename);
    static int writeFile(string outputPath, string sourceParh);
    static int getCurrentTimestamp();


    // static std::map<std::string, T> objectMap;

    // static void addSwapObject(string key, T) {
    //     objectMap.insert({key, T});
    // };

    // static T getSwapObject(string key) {
    //     auto it = objectMap.find(key);
    //     if (it != objectMap.end()) {
    //         return it->second;
    //     }
    //     return nullptr;
    // };

signals:
};

#endif // UTILS_H
