#ifndef TIMER_H
#define TIMER_H

#include <string>
#include <chrono>
#include <string>
#include <iostream>
#include <unordered_map>
#include <chrono>
#include <iomanip>

typedef std::pair<std::string, std::string> TIMER_KEY;
typedef std::pair<int, float> TIMER_VALUE;
typedef std::chrono::steady_clock::time_point TIMER_VALUE_SINGLE;

class Timer {
private:
    static std::unordered_map<TIMER_KEY, TIMER_VALUE> timer;
    static std::unordered_map<TIMER_KEY, bool> is_timing;
    static std::unordered_map<TIMER_KEY, TIMER_VALUE_SINGLE> single_timer;
    static void show_single_tick_info(std::string classname, std::string funcname, TIMER_VALUE timer_val);
public:
    static void tick(std::string classname, std::string funcname);
    static void show_info();
};

#endif