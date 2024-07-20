#pragma once

#include <iostream>
#include <ctime>
#include <string>
using namespace std;

string get_current_time();

#define __LOG_MSG(message, level) \
    "[" << get_current_time() << " " << __FILE__ ":" << to_string(__LINE__) << "\t" << level << "] " << message << endl

#ifdef DEBUG // DEBUG =========================================
#define LOG_DEBUG(message) cout << __LOG_MSG(message, "DEBUG")
#else 
#define LOG_DEBUG(message)
#endif // ======================================================

#define LOG_INFO(message) cout << __LOG_MSG(message, "INFO")
#define LOG_ERROR(message) cout << __LOG_MSG(message, "ERROR")
#define LOG_WARNING(message) cout << __LOG_MSG(message, "WARNING")
