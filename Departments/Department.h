#ifndef _DEPARTMENT_H_
#define _DEPARTMENT_H_

#include "../Employees/pilot.h"
#include "../Employees/FlightAttendant.h"
#include "../Employees/Medic.h"
#include "../Accounts/Account.h"

class Department
{
protected:
    std::string name;
    // std::vector <const Employee*> &employees;   // Aggregation
public:
  
    Department();
    Department (const std::string& dep_name);
    ~Department() = default;
};

#endif // Department class
