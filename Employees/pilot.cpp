#include "pilot.h"

Pilot ::Pilot() : Employee("", "", "", "", "", "", nullptr, Salary()), experience(0.0)
{
}

Pilot ::Pilot(
    const std::string &first, // firstName
    const std::string &last,  // lastName
    const std::string &id,    // id
    const std::string &pass,  // pass
    const std::string &dep,   // department
    const std::string &des,   // designation
    Account *account,         // account
    const Salary &salary,     // salary
    const double &exp)        // experience
    : Employee(first, last, id, pass, dep, des, account, salary), experience(exp)
{
          
}

void Pilot :: displayInfo() const
{
    std::cout << "\n\t ------ Your Bio-Data ------ " << std::endl;
    std::cout << *this << std::endl;
}

double Pilot ::calculateFlyingHours()
{
    readAttendanceFile();
    double hours = 0.0;
    for (int i=0; i < attendanceRecord.size(); i++)
    {
        time_t a = attendanceRecord.at(i).getArrival();
        time_t d = attendanceRecord.at(i).getDeparture();
        hours +=  static_cast<double> (d) - static_cast<double> (a);
    }
    return hours/3600;
}

double Pilot :: calculateSalary () 
{
    double hours = calculateFlyingHours();
    double diff = 0.0, bonus = 0.0, ded;

    if (hours > 176.0)  // Monthly average hours are 176
    { 
        diff = hours - 176;
        bonus = diff*this->salary.getHourlySalary();
        this->salary += bonus;
    }
    else if (hours < 176.0) // deducting salary if less than average
    {
        diff = 176.0 - hours;
        ded = diff*this->salary.getHourlySalary();
        this->salary -= ded;
    }
    return hours * this->salary.getHourlySalary();
}

std::ostream &operator<<(std::ostream &os, const Pilot &pilot)
{
    os << " First name : " << pilot.firstName << "\n Last name  : " << pilot.lastName << "\n Employee Id: " << pilot.id
       << "\n Password   : " << pilot.pass << "\n Department : " << pilot.department << "\n Designation: " << pilot.designation
       << "\n Experience : " << pilot.experience << std::endl;

    // Account Info

    os << "\n\n\t Account Info " << std::endl;
    os << " Account Number : " << pilot.getAccountNumber() << std::endl;
    os << " Account Balance: " << pilot.getBalance() << std::endl;
    os << "\n\n\t Salary Info " << std::endl;

    // Salary Info

    os << " Basic Salary : " << pilot.getBasicSalary() << "\n"
       << " Allowances   : " << pilot.getAllowances() << "\n"
       << " Hourly Wage  : " << pilot.getHourlySalary() << "\n"
       << " Deductions   : " << pilot.getDeductions() << std::endl;
    return os;
}
