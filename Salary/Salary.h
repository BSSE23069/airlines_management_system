#ifndef _SALARY_H_
#define _SALARY_H_

#include <iostream>
#include <string>

class Salary 
{
    private:
    
    double basicSalary;
    double allowances;
    double hourlyRate;
    double deductions;

    public:
    Salary();
    Salary(double, double, double hourly_rate = 0.0, double d = 0.0);

    // Setters
    void setBasicSalary (double);
    void setAllowances (double);
    void setDeductions (double);
    void setHourlyRate (double);

    // Getters 
    double getBasicSalary () const;
    double getAllowances () const;
    double getDeductions () const;
    double getHourlySalary () const;

    // Operator overloading
    Salary operator + (const Salary& sal);
    Salary& operator += (const Salary& sal);
    Salary& operator += (double bonus);
    Salary& operator -= (const Salary& sal);
    Salary& operator -= (double ded);
    Salary operator - (const Salary& sal);
    Salary operator * (const Salary& sal);
    friend std::ostream& operator << (std::ostream& os, const Salary& sal);
    friend std::istream& operator >> (std::istream& is,  Salary& sal);
};


#endif // Salary class