#ifndef _INSPECTION_H_
#define _INSPECTION_H_
#include "Employee.h"

class InspectionManager : public Employee
{
  int inspections;
public:
  InspectionManager();
  InspectionManager(const std::string &,  // firstName
                    const std::string &,              // lastName
                    const std::string &,              // id
                    const std::string &,              // pass
                    const std::string &,              // department
                    const std::string &,              // designation
                    Account *account,                 // account
                    const Salary &salary = Salary(),  // salary
                    int inspections = 0 );            // inspections

  int getInspections () const; 
  virtual void displayInfo() const override;
  virtual double calculateSalary () override;
  friend std::ostream &operator << (std::ostream &os, const InspectionManager& ins);
};

#endif // Inspection Manager