#ifndef TSINFO_H
#define TSINFO_H

#include <QString>
class TsInfo
{
public:

    QString name;

    QString duration;

    TsInfo();

    TsInfo(QString name, QString duration);
};

#endif // TSINFO_H
