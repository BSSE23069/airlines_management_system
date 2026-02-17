#ifndef _PILOT_H_
#define _PILOT_H_

#include "Employee.h"

class Pilot : public Employee
{
private:
    double experience;
public:
    Pilot();
    Pilot(
        const std::string &,             // firstName
        const std::string &,             // lastName
        const std::string &,             // id
        const std::string &,             // pass
        const std::string &,             // department
        const std::string &,             // designation
        Account *account,                // account
        const Salary &salary = Salary(), // salary
        const double &exp = 0.0);        // experience

    ~Pilot() = default;

    double getExperience () const {return experience;}

    virtual void displayInfo() const override;
    virtual double calculateSalary () override;

    double calculateFlyingHours();
    friend std::ostream &operator<<(std::ostream &os, const Pilot &pilot);
};

#endif // Pilot class