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
    static vector<string> splitStr(const string& s, const string& split);
    static UrlPart analyseUrl(const string& url);
    static void printVector(const vector<string>& list);
    static void downloadTsFile(const string& filePath, const string& tsUrl);
    static void mergeFile(const string& dir, const string& filename);
    static int writeFile(const string& outputPath, const string& sourceParh);
    static int getCurrentTimestamp();
signals:
};

#endif // UTILS_H
