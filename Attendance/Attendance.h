#ifndef _ATTENDANCE_H_
#define _ATTENDANCE_H_
#include "../nlohmann/json.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
using json = nlohmann ::json;


class Attendance
{
    std::time_t arrivalTime, departureTime;

public:
    Attendance();
    ~Attendance();
    Attendance(const std::time_t &arr, const std::time_t &dep);

    std::time_t getArrival () const;
    std::time_t getDeparture () const;

    void display () const;
};

#endif // Attendance class