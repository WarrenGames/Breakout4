#ifndef DATE_AND_TIME_H
#define DATE_AND_TIME_H

#include <string>
#include <ctime>

std::tm localtime_safe(std::time_t timer);

std::string returnCurrentTimeAndDate();

std::string returnCurrentDate();

#endif //DATE_AND_TIME_H