#ifndef _ADMIN_H_
#define _ADMIN_H_

#include "../Airlines.h"
#include "../Accounts/Account.h"
#include "../Accounts/AirlinesAccount.h"

class Admin : public User
{
public:
    // Constructors
    Admin();
    Admin(const std::string &,  // firstName
          const std::string &,  // lastName
          const std::string &,  // id
          const std::string &); // pass
    virtual ~Admin();

    // Overriden function
    virtual bool login (const std::string&, const std::string&) const override;
    virtual void displayInfo() const override;

    // Customer functions
    void displayCustomers () const;

    // Admin functions
    void addEmployee();
    void removeEmployee();
    void updateEmployee();
    void displayEmployees() const;
    void markAttendance();
    void transferSalary();
    void setBudget();
    void financialManagement();
    void viewAirlinesBalance();
    void viewTransactionReport();
    void setAirlinesBalance(double balance);
    friend std::ostream &operator<<(std::ostream &os, const Admin &admin);
};

#endif // Admin Controls