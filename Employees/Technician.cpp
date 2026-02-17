#include "Technician.h"

Technician :: Technician()
: Employee("", "", "", "", "", "", nullptr, Salary()), tier(1)
{

}

Technician :: Technician(
    const std::string &first, // firstName
    const std::string &last,  // lastName
    const std::string &id,    // id
    const std::string &pass,  // pass
    const std::string &dep,   // department
    const std::string &des,   // designation
    Account *account,         // account
    const Salary &salary,
    int tier)
    : Employee(first, last, id, pass, dep, des, account, salary)
{
  this->tier = tier;
}

int Technician :: getTier () const{
  return tier;
}          

double Technician :: calculateSalary ()
{
  return 0.0;
}

void Technician :: displayInfo() const 
{
    std::cout << "\n\t\t" <<  this->id << " BIO-DATA" << std::endl;
    std::cout << *this << std::endl;
}

std::ostream &operator << (std::ostream &os, const Technician &tech)
{
    os << " First name  : " << tech.firstName 
       << "\n Last name   : " << tech.lastName 
       << "\n Id          : " << tech.id
       << "\n Password    : " << tech.pass 
       << "\n Department  : " << tech.department 
       << "\n Designation : " << tech.designation 
       << "\n\n \t\t ACCOUNT INFO " << std::endl;
       os << tech.account 
       << "\n\n \t\t SALARY INFO " << std::endl;
       os << tech.salary << std::endl; 

    return os;
}
