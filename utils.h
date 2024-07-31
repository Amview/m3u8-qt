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
    static vector<string> splitStr(string s, const string& split);
    static UrlPart analyseUrl(string url);
    static void printVector(const vector<string>& list);
    static void downloadTsFile(const string& filePath, const string& tsUrl);
    static void mergeFile(const string& dir, const string& filename);
    static int writeFile(const string& outputPath, string sourceParh);
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
