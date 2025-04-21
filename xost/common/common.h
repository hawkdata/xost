

// common.h
#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <sstream>

#define LOG(msg)                                                              \
{                                                                         \
auto now = std::chrono::system_clock::now();                           \
auto now_c = std::chrono::system_clock::to_time_t(now);                \
std::tm now_tm{};                                                      \
localtime_r(&now_c, &now_tm);                                         \
std::stringstream ss;                                                \
ss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S") << " [Thread ID: "   \
<< std::this_thread::get_id() << "] " << msg;                      \
std::cout << ss.str() << std::endl;                                   \
}

#define LOG_ERROR(msg) LOG("[ERROR] " << msg)

#endif // COMMON_H