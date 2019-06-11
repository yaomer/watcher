#ifndef _WATCHER_H
#define _WATCHER_H

#include <set>
#include <vector>
#include <string>
#include "Manager.h"

class MacCmp {
public:
    bool operator()(const std::string& lhs,
                    const std::string& rhs) const
    {
        return lhs.compare(rhs) < 0;
    }
};

class Watcher {
public:
    Watcher();
    ~Watcher();
    void readConf();
    void reReadConf() { _table.clear(); readConf(); }
    void watch();
    void flush();
    void setDate();
    void getMacAddrs();
    void find();
    bool findMacAddr(std::string& s);
    void autoFlush();
    void initResFile();
    void updateWeekDays() { _weekDays++; }
    void visual();
    static const char *confFile;
    static const char *macFile;
    static const char *resFile;
private:
    std::string _date;
    std::set<std::string, MacCmp> _macAddrs;
    std::vector<Manager> _table;
    bool _flush = false;
    int _weekDays = 0;
};

#endif // _WATCHER_H
