#ifndef AirLinesAccount_H
#define AirLinesAccount_H
#include <iostream>
#include <fstream>
//#include "AccountsManagement.h"
#include "Account.h"
#include "../nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

class AirlinesAccount : public Account{
private:

    AirlinesAccount() {
        accountNumber = "AIRLinesAccount123";
        accountBalance = 0;
        employeeBudgetExists = false;
        passengerBudgetExists = false;
        planeCostBudgetExists = false;
        courierBudgetExists = false;
    }
    static AirlinesAccount *instance;
    // string accountNumber = "AIRLinesAccount123"; // Our account number
    // double accountBalance;                       // Our account balance

    // Following are the budgets
    double budgetEmployee;
    double budgetCustomer;
    double budgetPlaneCost;
    double budgetCourier;

    // Following bool values are to validate if a budget already exists or not
    bool employeeBudgetExists;
    bool passengerBudgetExists;
    bool planeCostBudgetExists;
    bool courierBudgetExists;

public:
//    string filepath = "c:\\Users\\HP\\Desktop\\Programming\\Project\\Testing\\2024-Spring-SE102TB-Project-se102b-e\\Accounts\\airlinesAccount.json";
//   string filepath = R"(C:\OOPS PROJECT\2024-Spring-SE102TB-Project-se102b-e\Accounts\airlinesAccount.json)";
//string filepath = "C:\\Users\\HP\\Desktop\\Programming\\Project\\Testing\\Testing 3\\2024-Spring-SE102TB-Project-se102b-e\\Accounts\\airlinesAccount.json";
string filepath = "C:\\OOPS_PROJECT_EXTENDED\\2024-Spring-SE102TB-Project-se102b-e\\Accounts\\airlinesAccount.json";
  json airlinesAccountData;

    static AirlinesAccount *getInstance()
    {
        if (!instance)
        {
            instance = new AirlinesAccount;
        }
        return instance;
    }
    void addAirinesBalance(double bal, string otherAccountNumber);
    void removeBalanceDirectly(string accNum, double bal);
    void generateReport(bool addOrRemove, double temp, double accountBalance, string otherAccountNumber);
    string getAccountNumber()
    {
        return accountNumber;
    }
    double getAccountBalance()
    {
        return accountBalance;
    }
    void setAccountNumber(string accNum)
    {
        accountNumber = accNum;
    }
    void setBalance(double bal)
    {
        loadAirlinesData();
        accountBalance = bal;
        airlinesAccountData["accountBalance"] = accountBalance;

        ofstream out(filepath);
        out << airlinesAccountData;
        out.close();
    }
    void setBudget();

    double getPlaneCostBudget()
    {
        return budgetPlaneCost;
    }

    void setPlaneCostBudget(double value);

    //    void airlinesAccountMenu();

    void deduceCompanyBalanceFromUnknownAccount(string accountNumber, double deducebalance);

    double getEmployeesBudget();

    double getCourierBudget();

    double getCustomerBudget();

    void callRevenueMenu();

    void viewTransactionReport();

    void setCustomerBudget(double value);
    void setEmployeesBudget(double value);
    void setCourierBudget(double value);
    void saveAirlinesAccountData();
    void loadAirlinesData();
};

#endif
