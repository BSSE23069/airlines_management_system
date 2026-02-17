#include "Medic.h"

Medic ::Medic()
    : Medic("", "", "", "", "", "", nullptr, Salary())
{
}

Medic ::Medic(
    const std::string &first, // firstName
    const std::string &last,  // lastName
    const std::string &id,    // id
    const std::string &pass,  // pass
    const std::string &dep,   // department
    const std::string &des,   // designation
    Account *account,         // account
    const Salary &salary)
    : Employee(first, last, id, pass, dep, des, account, salary)
{
}

double Medic ::calculateFlyingHours()
{
    readAttendanceFile();
    double hours = 0.0;
    for (int i = 0; i < attendanceRecord.size(); i++)
    {
        time_t a = attendanceRecord.at(i).getArrival();
        time_t d = attendanceRecord.at(i).getDeparture();
        hours += static_cast<double>(d) - static_cast<double>(a);
    }
    return hours / 3600;
}


double Medic ::calculateSalary()
{
    double hours = calculateFlyingHours();
    double diff = 0.0, bonus = 0.0, ded = 0.0;

    if (hours > 176.0) // Monthly average hours are 176
    {
        diff = hours - 176;
        bonus = diff * this->salary.getHourlySalary();
        this->salary += bonus;
    }
    else if (hours < 176.0) // deducting salary if less than average
    {
        diff = 176.0 - hours;
        ded = diff * this->salary.getHourlySalary();
        this->salary -= ded;
    }
    return hours * this->salary.getHourlySalary();
}


void Medic ::displayInfo() const
{
    std::cout << "\n\t #### Your Bio-Data #### " << std::endl;
    std::cout << *this << std::endl;
}


std::ostream &operator<<(std::ostream &os, const Medic &medic)
{
    os << " First name: " << medic.firstName << "\n Last name: " << medic.lastName << "\n Id       : " << medic.id
       << " Password  : " << medic.pass << "\n Department  : " << medic.department << "\n Designation : " << medic.designation << std::endl;

    // Account Information
    os << "\t Account Info " << std::endl;
    os << " Account Number : " << medic.getAccountNumber() << std::endl;
    os << " Account Balance: " << medic.getBalance() << std::endl;
    os << "\t Salary Info " << std::endl;

    // Salary Information
    os << " Basic Salary : " << medic.getBasicSalary() << "\n"
       << " Allowances   : " << medic.getAllowances() << "\n"
       << " Hourly Wage  : " << medic.getHourlySalary() << "\n"
       << " Deductions   : " << medic.getDeductions() << std::endl;

    return os;
}
