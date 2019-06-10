#include <chrono>
#include <sys/time.h>
#include "Manager.h"

// get seconds from Epoch
time_t Manager::now()
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return tv.tv_sec + tv.tv_usec / 1000000;
}

// len >= 11
const char *Manager::timeStr(char buf[], size_t len)
{
    struct tm tm;
    time_t seconds = now();
    localtime_r(&seconds, &tm);
    snprintf(buf, len, "%4d-%02d-%02d",
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    return buf;
}

void Manager::initLoginTime()
{
    _loginTime = now();
}

void Manager::updateTimeOfDay()
{
    _timeOfDay += now() - _loginTime;
    _loginTime = 0;
}

void Manager::initTimeOfDay()
{
    _timeOfDay = 0;
}
