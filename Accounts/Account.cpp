#include <iostream>
using namespace std;
#include "Account.h"
#include "AirlinesAccount.h"
#include "AccountsManagement.h"
#include "ErrorManagement.h"

void Account ::loadRevenue()
{

    ifstream in(filepath);
    if (in.is_open())
    {
        in >> revenue;
        in.close();
    }
}

bool Account ::addBalance(double bal, string departmentName)
{
    loadRevenue();
    AirlinesAccount::getInstance()->loadAirlinesData();
    if (departmentName == "Plane maintainance")
    {
        if (bal > AirlinesAccount::getInstance()->getPlaneCostBudget())
        {
            cout << "Plane Maintainance Budget Surpassed!" << endl;
            return false;
        }
    }
    if (departmentName == "Employees")
    {
        if (bal > AirlinesAccount::getInstance()->getEmployeesBudget())
        {
            cout << "Employee Department Budget Surpassed!" << endl;
            return false;
        }
    }

    double temp = accountBalance;
    accountBalance += bal;
    cout << "An addition has occured in the previous balance of " << temp << " and balance has been updated to " << accountBalance << " successfully!" << endl;
    AirlinesAccount::getInstance()->removeBalanceDirectly(accountNumber, bal);

    if (departmentName == "Employees")
    {
        AirlinesAccount::getInstance()->setEmployeesBudget(AirlinesAccount::getInstance()->getEmployeesBudget() - bal); // Update the budget for Employees department
    }
    if (departmentName == "Plane maintainance")
    {
        AirlinesAccount::getInstance()->setPlaneCostBudget(AirlinesAccount::getInstance()->getPlaneCostBudget() - bal); // Update the budget for Plane cost department
    }
    json tempRevenue;
    tempRevenue["amount"] = bal;
    tempRevenue["transactionType"] = false;
    revenue["transactions"].push_back(tempRevenue);
    saveRevenue();
    return true;
}

void Account ::removeBalance(double bal)
{
    loadRevenue();
    string verifiedAccountNumber = "0";
    // verifiedAccountNumber = AccountsManagement::getInstance()->verifyAccounts(accountNumber);

    double temp = accountBalance;
    accountBalance -= bal;
    cout << "A deduction has occured in previous balance of " << temp << " and balance has been updated to " << accountBalance << " successfully!" << endl;
    AirlinesAccount::getInstance()->addAirinesBalance(bal, accountNumber);

    json tempRevenue;
    tempRevenue["amount"] = bal;
    tempRevenue["transactionType"] = true;
    revenue["transactions"].push_back(tempRevenue);

    saveRevenue();
}

string Account ::getAccountNumber()
{
    return accountNumber;
}
double Account ::getBalance()
{
    return accountBalance;
}

void Account ::setAccountNumber(string num)
{
    accountNumber = num;
}
void Account ::setBalance(double bal)
{
    accountBalance = bal;
}

bool Account::addBalanceDirectly(string accNum, double bal, string departmentName)
{
    loadRevenue();
    AirlinesAccount::getInstance()->loadAirlinesData();
    if (departmentName == "Flights")
    {
        if (bal > AirlinesAccount::getInstance()->getCustomerBudget())
        {
            cout << "Flights Department Budget Surpassed!" << endl;
            return false;
        }
    }

    string verifiedAccountNumber = "0";
    // verifiedAccountNumber = AccountsManagement::getInstance()->verifyAccounts(accNum);

    double temp = accountBalance;
    accountBalance += bal;

    if (departmentName == "Flights")
    {
        AirlinesAccount::getInstance()->setCustomerBudget(AirlinesAccount::getInstance()->getCustomerBudget() - bal); // Update the budget for flights department
        AirlinesAccount::getInstance()->saveAirlinesAccountData();
    }

    cout << "An addition has occurred in the previous balance of " << temp << " and balance has been updated to " << accountBalance << " successfully!" << endl;
    // AirlinesAccount::getInstance()->set
    AirlinesAccount::getInstance()->removeBalanceDirectly(accNum, bal);

    json tempRevenue;
    tempRevenue["amount"] = bal;
    tempRevenue["transactionType"] = false;
    revenue["transactions"].push_back(tempRevenue);

    saveRevenue();

    return true;
}

void Account::removeBalanceDirectly(string accNum, double bal)
{
    loadRevenue();

    string verifiedAccountNumber = "0";
    // verifiedAccountNumber = AccountsManagement::getInstance()->verifyAccounts(accNum);

    double temp = accountBalance;
    accountBalance -= bal;
    cout << "A deduction has occurred in the previous balance of " << temp << " and balance has been updated to " << accountBalance << " successfully!" << endl;
    AirlinesAccount::getInstance()->addAirinesBalance(bal, accNum);

    json tempRevenue;
    tempRevenue["amount"] = bal;
    tempRevenue["transactionType"] = true;
    revenue["transactions"].push_back(tempRevenue);

    saveRevenue();
}

bool Account ::addBalanceUnknownAcc(string accNum, double bal, string departmentName)
{
    loadRevenue();
    AirlinesAccount::getInstance()->loadAirlinesData();
    if (departmentName == "Plane maintainance")
    {
        if (bal > AirlinesAccount::getInstance()->getPlaneCostBudget())
        {
            cout << "Plane Maintainance Budget Surpassed!" << endl;
            return false;
        }
    }

    if (departmentName == "Courier")
    {
        if (bal > AirlinesAccount::getInstance()->getCourierBudget())
        {
            cout << "Courier Department Budget Surpassed!" << endl;
            return false;
        }
    }

    cout << "An addition has occurred in the balance of account Number: " << accNum << endl;
    AirlinesAccount::getInstance()->removeBalanceDirectly(accNum, bal);

    if (departmentName == "Plane maintainance")
    {
        AirlinesAccount::getInstance()->setPlaneCostBudget(AirlinesAccount::getInstance()->getPlaneCostBudget() - bal); // Update the budget for Plane cost department
        AirlinesAccount::getInstance()->getInstance()->saveAirlinesAccountData();
    }

    json tempRevenue;
    tempRevenue["amount"] = bal;
    tempRevenue["transactionType"] = false;
    revenue["transactions"].push_back(tempRevenue);
    saveRevenue();

    return true;
}

void Account ::removeBalanceUnknownAcc(string accNum, double bal)
{
    loadRevenue();

    cout << "A deduction has occurred in the balance of account Number: " << accNum << endl;
    AirlinesAccount::getInstance()->addAirinesBalance(bal, accNum);

    json tempRevenue;
    tempRevenue["amount"] = bal;
    tempRevenue["transactionType"] = false;
    revenue["transactions"].push_back(tempRevenue);
    saveRevenue();
}

void Account ::saveRevenue()
{

    ofstream out(filepath);
    out << revenue;
    out.close();
}

void Account ::revenueMenu()
{
    loadRevenue();

    cout << "[1]Display Revenue Report, [2]Display Loss Report, [3]Display Overall Profit/Loss Report: ";
    int x;
    cin >> x;
    if (x == 1)
    {
        double totalRevenue = 0;

        for (int i = 0; i < revenue["transactions"].size(); i++)
        {
            if (revenue["transactions"][i]["transactionType"] == true)
            {
                double temp = 0;
                temp = revenue["transactions"][i]["amount"];
                totalRevenue += temp;
            }
        }

        cout << "Total Revenue: " << totalRevenue << endl;
    }
    if (x == 2)
    {
        double lostMoney = 0;

        for (int i = 0; i < revenue["transactions"].size(); i++)
        {
            if (revenue["transactions"][i]["transactionType"] == false)
            {
                double temp = 0;
                temp = revenue["transactions"][i]["amount"];
                lostMoney += temp;
            }
        }

        cout << "Total Lost Money: " << lostMoney << endl;
    }
    if (x == 3)
    {
        double profit = 0;

        double totalRevenue = 0;

        for (int i = 0; i < revenue["transactions"].size(); i++)
        {
            if (revenue["transactions"][i]["transactionType"] == true)
            {
                double temp = 0;
                temp = revenue["transactions"][i]["amount"];
                totalRevenue += temp;
            }
        }

        double lostMoney = 0;

        for (int i = 0; i < revenue["transactions"].size(); i++)
        {
            if (revenue["transactions"][i]["transactionType"] == false)
            {
                double temp2 = 0;
                temp2 = revenue["transactions"][i]["amount"];
                lostMoney += temp2;
            }
        }

        profit = (totalRevenue - lostMoney);

        cout << "Profit/Loss: " << profit << endl;
    }
}
