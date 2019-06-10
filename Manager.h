#ifndef _MANAGER_H
#define _MANAGER_H

#include <string>

class Manager {
public:
    std::string& name() { return _name; }
    std::string& mac() { return _mac; }
    bool online() const { return _online; }
    time_t loginTime() const { return _loginTime; }
    size_t timeOfDay() const { return _timeOfDay; }
    void setOnline(bool on) { _online = on; }
    void initLoginTime();
    void updateTimeOfDay();
    void initTimeOfDay();
    static time_t now();
    static const char *timeStr(char *buf, size_t len);
private:    
    std::string _name;
    std::string _mac;
    bool _online = false;
    time_t _loginTime = 0;
    size_t _timeOfDay = 0;
};

#endif // _MANAGER_H
