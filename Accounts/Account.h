#ifndef Account_H
#define Account_H

#include <iostream>
// #include "AirlinesAccount.h"
// #include "AccountsManagement.h"
#include "../nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

class Account{
    protected:
    string accountNumber;
    double accountBalance;

    public:
    json revenue;
//    string filepath = "C:\\Users\\HP\\Desktop\\Programming\\Project\\Testing\\Testing 3\\2024-Spring-SE102TB-Project-se102b-e\\Accounts\\revenue.json";
    string filepath = "C:\\OOPS_PROJECT_EXTENDED\\2024-Spring-SE102TB-Project-se102b-e\\Accounts\\revenue.json";
    Account(string accNum){
        accountNumber = accNum;
        accountBalance = 0.0;
    }
    Account(){
        accountBalance = 0;
        accountNumber = "";

    }
    
    bool addBalance(double bal, string departmentName);
    void removeBalance(double bal);
    // virtual void changeCurrency(); //In progress

    string getAccountNumber();
    double getBalance();


    void setAccountNumber(string num);
    void setBalance(double bal);
    // void setAirlinesBalance(double airBal); //Not to be used in present
    virtual void removeBalanceDirectly(string accNum, double bal);
    bool addBalanceDirectly(string accNum, double bal, string departmentName);
    bool addBalanceUnknownAcc(string accNum, double bal, string departmentName);
    void removeBalanceUnknownAcc(string accNum, double bal);
    void saveRevenue();
    void loadRevenue();
    void revenueMenu();
};


//Work In Progress!
//Gonna make EmployeeAccount, PassengerAccount, CourierServiceAccount and PlaneCostAccount as seperate classes that will inherit from class Account
//Unique Attributes:- EmployeeAccount -> Salary, PassengerAccount -> Flight Cost, CourierServiceAccount -> ServiceCost and PlaneCostAccount -> PlaneMaintainanceCost
//Taking loans


//Resolve These!: -
//Package.h calls removeBalanceDirectly but provides three arguments instead of 2!

#endif


