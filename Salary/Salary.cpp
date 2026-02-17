#include "Salary.h"

// Default Constructor
Salary ::Salary() : basicSalary(0.0), allowances(0.0), hourlyRate(0.0), deductions(0.0)
{
}
// Parameterized Constructor
Salary ::Salary(double b, double a, double h, double d) : basicSalary(b), allowances(a), hourlyRate(h), deductions(d)
{
}

// Setters
void Salary ::setBasicSalary(double basic)
{
    this->basicSalary = basic;
}
void Salary ::setAllowances(double a)
{
    this->allowances = a;
}
void Salary ::setDeductions(double d)
{
    this->deductions = d;
}
void Salary ::setHourlyRate(double h_r)
{
    this->hourlyRate = h_r;
}

// Getters
double Salary ::getBasicSalary() const
{
    return basicSalary;
}
double Salary ::getAllowances() const
{
    return allowances;
}
double Salary ::getDeductions() const
{
    return deductions;
}
double Salary ::getHourlySalary() const
{
    return hourlyRate;
}

// Operator overloading
Salary Salary ::operator+(const Salary &sal)
{
    Salary temp;
    temp.basicSalary = this->basicSalary + sal.basicSalary;
    return temp;
}

Salary Salary ::operator-(const Salary &sal)
{
    Salary temp;
    temp.basicSalary = this->basicSalary - sal.basicSalary;
    return temp; 
}

Salary Salary ::operator*(const Salary &sal)
{
    Salary temp;
    temp.basicSalary = this->basicSalary * sal.basicSalary;
    return temp; 
}

Salary& Salary :: operator+=(const Salary &sal)
{
    this->basicSalary+=sal.basicSalary;
    return *this;
}

Salary& Salary :: operator += (double bonus)
{
    this->basicSalary += bonus;
    return *this;
}

Salary& Salary :: operator -= (double ded)
{
    this->basicSalary -= ded;
    return *this;
}

Salary& Salary :: operator-=(const Salary &sal)
{
    this->basicSalary-=sal.basicSalary;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Salary &sal)
{
    os << std::endl;
    os << " Basic Salary     : " << sal.basicSalary << "\n";
    os << " Allowances Salary: " << sal.allowances << "\n";
    os << " Deductions       : " << sal.deductions << "\n";
    os << " Hourly Salary    : " << sal.hourlyRate << "\n";
    return os;
}

std::istream& operator >> (std::istream& is,  Salary& sal)
{
    std::cout << "\n Enter base salary: "; is >> sal.basicSalary;
    std::cout << "\n Enter allowances : "; is >> sal.allowances;
    std::cout << "\n Enter deductions : "; is >> sal.deductions;
    std::cout << "\n Enter hourly salary: "; is >> sal.hourlyRate;
    return is;
}
