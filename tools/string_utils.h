//
// Created by hua on 2024/9/15.
//

#ifndef M3U8_STRING_UTILS_H
#define M3U8_STRING_UTILS_H


#include <QObject>
#include "string"

using namespace std;
class StringUtils : public QObject {
Q_OBJECT
public:
    static bool startWidth(const string& str, const string& prefix);
};


#endif //M3U8_STRING_UTILS_H
