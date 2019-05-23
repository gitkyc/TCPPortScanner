#include "scanresult.h"

ScanResult::ScanResult()
{

}

QString ScanResult::ip()
{
    return m_ip;
}

void ScanResult::setIp(const QString &ip)
{
    m_ip = ip;
}

bool ScanResult::found()
{
    return m_found;
}

void ScanResult::setFound(bool found)
{
    m_found = found;
}
