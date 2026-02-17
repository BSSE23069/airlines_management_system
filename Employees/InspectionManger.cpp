#include "InspectionManager.h"

InspectionManager :: InspectionManager()
    : Employee("", "", "", "", "", "", nullptr, Salary()), inspections(0)
{
     
}

InspectionManager :: InspectionManager(
    const std::string &first, // firstName
    const std::string &last,  // lastName
    const std::string &id,    // id
    const std::string &pass,  // pass
    const std::string &dep,   // department
    const std::string &des,   // designation
    Account *account,         // account
    const Salary &salary,
    int inspections)
    : Employee(first, last, id, pass, dep, des, account, salary)
{
  this->inspections = inspections;
}

int InspectionManager :: getInspections () const{
  return inspections;
}

double InspectionManager :: calculateSalary () 
{
  return 0.0;
}


void InspectionManager :: displayInfo() const 
{
  std::cout << *this << std::endl;
}

std::ostream &operator << (std::ostream &os, const InspectionManager &ins)
{
    os << " First name  : "   << ins.firstName 
       << "\n Last name   : " << ins.lastName 
       << "\n Id          : " << ins.id
       << "\n Password    : " << ins.pass 
       << "\n Department  : " << ins.department 
       << "\n Designation : " << ins.designation 
       << "\n\n \t\t ACCOUNT INFO " << std::endl;
       os << ins.account->getAccountNumber()
       << "\n\n \t\t SALARY INFO " << std::endl;
       os << ins.salary << std::endl; 
    return os;
}


