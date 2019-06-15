#include <python2.7/Python.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "Watcher.h"
#include "Manager.h"

// 配置文件
const char *Watcher::confFile = "./watch.conf";
// scan.sh产生的中间文件
const char *Watcher::macFile = "./mac.txt";
// 存储监测数据
const char *Watcher::resFile = "./res.csv";

Watcher::Watcher()
{
    readConf();
    setDate();
    initResFile();
    // 开启python(run.sh/$Python)解释器
    Py_Initialize();
}

Watcher::~Watcher()
{
    // 关闭python解释器
    Py_Finalize();
}

void Watcher::setDate()
{
    char buf[32];
    Manager::timeStr(buf, sizeof(buf));
    _date.clear();
    _date.append(buf);
}

// 从mac.txt中读取到所有MAC地址
void Watcher::getMacAddrs()
{
    std::ifstream ifs(macFile, std::ios::in);
    char buf[1024];

    _macAddrs.clear();
    while (ifs.getline(buf, sizeof(buf))) {
        char *p = buf;
        char *ep = buf + strlen(buf);
        while (p < ep && isspace(*p))
            p++;
        _macAddrs.insert(p);
        bzero(buf, sizeof(buf));
    }
}

bool Watcher::findMacAddr(std::string& s)
{
    return _macAddrs.find(s) != _macAddrs.end();
}

void Watcher::find()
{
    system("./scan.sh");
    getMacAddrs();
}

// 程序的主循环
void Watcher::watch()
{
    for (auto& it : _table) {
        if (it.online()) {
            if (!findMacAddr(it.mac())) {
                it.setOnline(false);
                it.updateTimeOfDay();
                std::cout << it.name() << " is gone, online time is "
                          << it.timeOfDay() << " s" << std::endl;
            }
        } else {
            if (findMacAddr(it.mac())) {
                std::cout << it.name() << " is coming" << std::endl;
                it.setOnline(true);
                it.initLoginTime();
            }
        }
    }
    autoFlush();
}

// 将监测数据flush到文件中
void Watcher::flush()
{
    std::ofstream ofs(resFile, std::ios::app);
    std::string s;
    char buf[32];

    for (auto& it : _table) {
        snprintf(buf, sizeof(buf), "%.3g", it.timeOfDay() * 1.0 / 3600);
        it.initTimeOfDay();
        s += _date;
        s += ", ";
        s += it.name();
        s += ", ";
        s += buf;
        s += "\n";
        ofs.write(s.c_str(), s.size());
        s.clear();
    }
    setDate();
    updateWeekDays();
}

void Watcher::autoFlush()
{
    struct tm tm;
    time_t seconds = Manager::now();
    localtime_r(&seconds, &tm);
    if (!_flush) {
        if (tm.tm_hour >= 23) {
            _flush = true;
            flush();
            reReadConf();
            visual();
        }
    } else {
        if (tm.tm_hour < 23)
            _flush = false;
    }
}

// 读取配置文件watch.conf
void Watcher::readConf()
{
    std::ifstream ifs(confFile, std::ios::in);
    char buf[1024];
    Manager mgr;

    while (ifs.getline(buf, sizeof(buf))) {
        char *p = buf;
        char *ep = buf + strlen(buf);
        while (p < ep && isspace(*p))
            p++;
        for ( ; p < ep && !isspace(*p); p++)
            mgr.name().push_back(*p);
        while (p < ep && isspace(*p))
            p++;
        for ( ; p < ep && !isspace(*p); p++)
            mgr.mac().push_back(*p);
        _table.push_back(mgr);
        mgr.name().clear();
        mgr.mac().clear();
        bzero(buf, sizeof(buf));
    }
}

// 初始化res.csv，只能在文件不存在时初始化一次
void Watcher::initResFile()
{
    std::ifstream ifs(resFile, std::ios::in);
    if (ifs) return;
    std::ofstream ofs(resFile, std::ios::app);
    std::string s("date, name, time\n");
    ofs.write(s.c_str(), s.size());
}

void Watcher::visual()
{
    if (_weekDays >= 7) {
        PyRun_SimpleString("import os");
        // 必须使用python3执行visual.py
        PyRun_SimpleString("os.system('python3 ./visual.py')");
        _weekDays = 0;
    }
}
