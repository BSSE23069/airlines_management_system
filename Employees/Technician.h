#ifndef _TECHNICIAN_H_
#define _TECHNICIAN_H_
#include "Employee.h"

class Technician : public Employee
{
  int tier; // tier 1, 2, or 3
public:
  Technician();
  Technician(const std::string &,              // firstName
             const std::string &,              // lastName
             const std::string &,              // id
             const std::string &,              // pass
             const std::string &,              // department
             const std::string &,              // designation
             Account *account,                 // account
             const Salary &salary = Salary(),  // salary
             int tier = 1);                    // tier

  int getTier () const;           
  virtual double calculateSalary () override;
  virtual void displayInfo() const override;
  friend std::ostream &operator << (std::ostream &os, const Technician& tech);
};

#endif // Inspection Manager