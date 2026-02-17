#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_

#include "../Users/User.h"
#include "../Attendance/Attendance.h"   // Attendance header
#include "../Salary/Salary.h"           // Salary header
#include "../Accounts/Account.h"        // Account Header

class Employee : public User            // Abstract class 
{
protected:

    std::string department, designation;
    Account* account;                      // Aggregation 
    Salary salary;                         // Composition 
    std::vector <Attendance> attendanceRecord;

    json json_attendance;
    int absents, presents;

public:
    // Constructors
    Employee();
    Employee(const std::string &, // firstName
             const std::string &, // lastName
             const std::string &, // id
             const std::string &, // pass 
             const std::string &, // department 
             const std::string &, // designation 
             Account* account,                        // account
             const Salary& salary  = Salary());       // salary 

    virtual ~Employee() = default;

    // Getters
    std::string getDepartment() const;
    std::string getDesignation() const;
    double getSalary() const;
    std::string getAccountNumber () const;
    double getBalance () const;
    double getBasicSalary () const;
    double getAllowances () const;
    double getDeductions () const;
    double getHourlySalary () const;
    int getAttendanceRecordSize() const;
    int getPresents () const;
    int getAbsents () const;
    
    
    // Setters
    void setDepartment(std::string &); 
    void setDesignation(std::string &);
    void setSalary(double sal);
    void setAccountNumber(string num);
    void setBalance(double bal);
    // void setAbsents (int a);
    // void setPresents (int p);

    void viewAttendanceRecord ( void );
    void readAttendanceFile ( void ) ;
    void markAttendance (  time_t&,  time_t& );
    void updateAttendanceFile ( void );
    void deposit (double amount);
    double calculateAttendancePercentage ();

    // Override
    virtual bool login (const std::string& u_name, const std::string& pass) const override;
    virtual double calculateSalary () = 0;
    // Pure virtual function
};


#endif // class Employee