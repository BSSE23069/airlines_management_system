#ifndef _MEDIC_H_
#define _MEDIC_H_

#include "Employee.h"

class Medic : public Employee
{
public:
    Medic();
    Medic(const std::string &,              // firstName
          const std::string &,              // lastName
          const std::string &,              // id
          const std::string &,              // pass
          const std::string &,              // department
          const std::string &,              // designation
          Account *account,                 // account
          const Salary &salary = Salary()); // salary

    virtual ~Medic(){

    }
    double calculateFlyingHours ();
    virtual double calculateSalary () override;
    virtual void displayInfo() const override;
    friend std::ostream &operator << (std::ostream &os, const Medic &medic);
};

#endif // Medic class
