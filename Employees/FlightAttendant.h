#ifndef _FLIGHT_ATTENDANT_H_
#define _FLIGHT_ATTENDANT_H_

#include "Employee.h"

class FlightAttendant : public Employee
{
public:
    FlightAttendant();
    FlightAttendant(
        const std::string &,              // firstName
        const std::string &,              // lastName
        const std::string &,              // id
        const std::string &,              // pass
        const std::string &,              // department
        const std::string &,              // designation
        Account *account,                 // account
        const Salary &salary = Salary()); // salary

    // Samer your methods go here

    double calculateFlyingHours ();
    virtual double calculateSalary () override;
    virtual void displayInfo() const override;

    friend std::ostream &operator<<(std::ostream &os, const FlightAttendant &fa);
};

#endif // FlightAttendant