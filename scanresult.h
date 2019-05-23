#ifndef SCANRESULT_H
#define SCANRESULT_H

#include <QString>

class ScanResult
{
public:
    ScanResult();

    QString ip();
    void setIp(const QString &ip);

    bool found();
    void setFound(bool found);

private:
    QString m_ip;
    bool m_found;
};

#endif // SCANRESULT_H
