#include "Attendance.h"

Attendance ::Attendance() : arrivalTime{}, departureTime{}
{
    
}

Attendance ::~Attendance()
{

}

Attendance ::Attendance(const std::time_t &arr, const std::time_t &dep) :arrivalTime(arr), departureTime(dep)
{

}

void Attendance ::display() const
{
    if (this->arrivalTime == this->departureTime)
    {
        std::tm *timeinfo = std::localtime(&arrivalTime);
        char buffer[80];
        std::strftime(buffer, 80, "%Y-%m-%d", timeinfo);
        std::cout << "\n You were absent on " << buffer << std::endl;
    }
    else
    {
        std::cout << "\n Arrival   Time : " << ctime(&arrivalTime) << std::endl;
        std::cout << " Departure Time : " << ctime(&departureTime) << std::endl;
    }
}

// time_t getter
std::time_t Attendance ::getArrival() const
{
    return arrivalTime;
}

std::time_t Attendance ::getDeparture() const
{
    return departureTime;
}
