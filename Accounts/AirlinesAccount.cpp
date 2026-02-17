#include "AirlinesAccount.h"
#include <ctime>
#include "../Accounts/Account.h"
#include <sstream>

AirlinesAccount *AirlinesAccount::instance = 0;
Account a1;

void AirlinesAccount ::addAirinesBalance(double bal, string otherAccountNumber)
{
    loadAirlinesData();

    double temp = accountBalance;
    accountBalance += bal;
    cout << "Airlines Account has been added with " << bal << endl;
    cout << "Previous balance: " << temp << endl;
    cout << "New balance: " << accountBalance << endl;

    airlinesAccountData["accountBalance"] = accountBalance;

    ofstream out(filepath);
    out << airlinesAccountData;
    out.close();

    generateReport(true, temp, accountBalance, otherAccountNumber);
}

void AirlinesAccount :: removeBalanceDirectly(string accNum, double bal)
{
    loadAirlinesData();

    double temp = accountBalance;
    accountBalance -= bal;
    cout << "Airlines Account has been deduced with " << bal << endl;
    cout << "Previous balance: " << temp << endl;
    cout << "New balance: " << accountBalance << endl;

    airlinesAccountData["accountBalance"] = accountBalance;

    ofstream out(filepath);
    out << airlinesAccountData;
    out.close();

    generateReport(false, temp, accountBalance, accNum);
    // cout << "Before returning from removeAirlinesBalance!" << endl;
    return;
}

void AirlinesAccount ::generateReport(bool addOrRemove, double temp, double accountBalance, string otherAccountNumber)
{ // If addOrRemove is true, it means that there was an addition in balance, otherwise deduction

    time_t now = time(NULL);
    string stringNow = ctime(&now);
    cout << "Generating report..." << endl;
    ofstream out("airlineTransaction.txt", ios::app);
    string report;
    if (addOrRemove == true)
    {
        out << "Stauts: Addition, From Account: " << otherAccountNumber << " to Airlines Account: " << accountNumber << ", Previous Balance: " << temp << ", New Balance: " << accountBalance << endl;
        out << "Transaction Time: " << stringNow << endl;
        out << "--------------------" << endl;
    }
    else if (addOrRemove == false)
    {
        out << "Stauts: Deduction, From Account: " << otherAccountNumber << " to Airlines Account: " << accountNumber << ", Previous Balance: " << temp << ", New Balance: " << accountBalance << endl;
        out << "Transaction Time: -" << stringNow << endl;
        out << "--------------------" << endl;
    }
    out.close();
    cout << "Report has been generated!" << endl;
    return;
}

void AirlinesAccount ::setBudget()
{
    loadAirlinesData();
    cout << "Set Budget For, [1]Employees Department, [2]Flight Department, [3]Courier Service Department, [4]Plane Maintainance Department: ";
    int x;
    cin >> x;
    if (x == 1)
    {
        if (employeeBudgetExists)
        { // Show existing budget if exists
            cout << "Current Budget: $" << budgetEmployee << endl;
        }
        cout << "New Budget: $";
        double tempBudget;
        cin >> tempBudget;
    
        if(tempBudget > accountBalance){
            cout << "The Budget Can Not Be Set, Accoung Balance Is Low!" << endl;
            return;
        }

        budgetEmployee = tempBudget;
        accountBalance -= tempBudget;
        cout << "The budget has been set!" << endl;
        employeeBudgetExists = true;
        airlinesAccountData["employeeBudgetExists"] = employeeBudgetExists;
        airlinesAccountData["budgetEmployee"] = budgetEmployee;

        ofstream out(filepath);
        out << airlinesAccountData;
        out.close();
    }
    if (x == 2)
    {
        if (passengerBudgetExists)
        { // Show existing budet if exists
            cout << "Current Budget: $" << budgetCustomer << endl;
        }
        cout << "New Budget: $";
        double tempBudget;
        cin >> tempBudget;
    
        if(tempBudget > accountBalance){
            cout << "The Budget Can Not Be Set, Accoung Balance Is Low!" << endl;
            return;
        }

        budgetCustomer = tempBudget;
        accountBalance -= tempBudget;
        cout << "The budget has been set!" << endl;
        passengerBudgetExists = true;
        airlinesAccountData["passengerBudgetExists"] = passengerBudgetExists;
        airlinesAccountData["budgetCustomer"] = budgetCustomer;

        ofstream out(filepath);
        out << airlinesAccountData;
        out.close();
    }
    if (x == 3)
    {
        if (courierBudgetExists)
        { // Show existing budget if exists
            cout << "Current Budget: $" << budgetCourier << endl;
        }
        cout << "New Budget: $";
        double tempBudget;
        cin >> tempBudget;
    
        if(tempBudget > accountBalance){
            cout << "The Budget Can Not Be Set, Accoung Balance Is Low!" << endl;
            return;
        }

        budgetCourier = tempBudget;
        accountBalance -= tempBudget;
        cout << "The budget has been set!" << endl;
        courierBudgetExists = true;
        airlinesAccountData["courierBudgetExists"] = courierBudgetExists;
        airlinesAccountData["budgetCourier"] = budgetCourier;

        ofstream out(filepath);
        out << airlinesAccountData;
        out.close();
    }
    if (x == 4)
    {
        if (planeCostBudgetExists)
        { // Show existing budget if exists
            cout << "Current Budget: $" << budgetPlaneCost << endl;
        }
        cout << "New Budget: $";
        double tempBudget;
        cin >> tempBudget;
    
        if(tempBudget > accountBalance){
            cout << "The Budget Can Not Be Set, Accoung Balance Is Low!" << endl;
            return;
        }

        budgetPlaneCost = tempBudget;
        accountBalance -= tempBudget;
        cout << "The budget has been set!" << endl;
        planeCostBudgetExists = true;
        airlinesAccountData["planeCostBudgetExists"] = planeCostBudgetExists;
        airlinesAccountData["budgetPlaneCost"] = budgetPlaneCost;

        ofstream out(filepath);
        out << airlinesAccountData;
        out.close();
    }

    return;
}

void AirlinesAccount ::setPlaneCostBudget(double value)
{
    budgetPlaneCost = value;
}

void airlinesAccountMenu()
{
    cout << "[1]Set Budgets, [2]View Reports: ";
    int x;
    cin >> x;
    if (x == 1)
    {
        AirlinesAccount::getInstance()->setBudget();
    }
    if (x == 2)
    {
        // AccountsManagement::getInstance()->
    }
}

void AirlinesAccount ::deduceCompanyBalanceFromUnknownAccount(string newAccountNumber, double deducebalance)
{
    double temp = accountBalance;
    accountBalance -= deducebalance;

    generateReport(false, temp, accountBalance, newAccountNumber);
}

double AirlinesAccount ::getEmployeesBudget()
{
    return budgetEmployee;
}

double AirlinesAccount ::getCourierBudget()
{
    return budgetCourier;
}

double AirlinesAccount ::getCustomerBudget()
{
    return budgetCustomer;
}

void AirlinesAccount ::callRevenueMenu()
{
    a1.revenueMenu();
}

void AirlinesAccount ::viewTransactionReport()
{

    ifstream in("airlineTransaction.txt");
    if (in.is_open())
    {
        string data;
        stringstream buffer;
        buffer << in.rdbuf();
        data = buffer.str();

        data = buffer.str();
        cout << data;
        cout << endl;
        in.close();
    }
    else
    {
        cout << "airlinesTransaction.txt doesn't exist!" << endl;
    }
}

void AirlinesAccount ::setCustomerBudget(double value)
{
    budgetCustomer = value;
}
void AirlinesAccount ::setEmployeesBudget(double value)
{
    budgetEmployee = value;
}
void AirlinesAccount ::setCourierBudget(double value)
{
    budgetCourier = value;
}

void AirlinesAccount ::saveAirlinesAccountData()
{

    loadAirlinesData();

    airlinesAccountData["employeeBudgetExists"] = employeeBudgetExists;
    airlinesAccountData["passengerBudgetExists"] = passengerBudgetExists;
    airlinesAccountData["planeCostBudgetExists"] = planeCostBudgetExists;
    airlinesAccountData["courierBudgetExists"] = courierBudgetExists;

    airlinesAccountData["budgetEmployee"] = budgetEmployee;
    airlinesAccountData["budgetCustomer"] = budgetCustomer;
    airlinesAccountData["budgetPlaneCost"] = budgetPlaneCost;
    airlinesAccountData["budgetCourier"] = budgetCourier;

    airlinesAccountData["accountBalance"] = accountBalance;
}

void AirlinesAccount ::loadAirlinesData()
{

    ifstream in(filepath);
    if (in.is_open())
    {

        in >> airlinesAccountData;
        in.close();

        if (!airlinesAccountData.contains("employeeBudgetExists"))
        {
            airlinesAccountData["employeeBudgetExists"] = false;
        }
        if (!airlinesAccountData.contains("passengerBudgetExists"))
        {
            airlinesAccountData["passengerBudgetExists"] = false;
        }
        if (!airlinesAccountData.contains("planeCostBudgetExists"))
        {
            airlinesAccountData["planeCostBudgetExists"] = false;
        }
        if (!airlinesAccountData.contains("courierBudgetExists"))
        {
            airlinesAccountData["courierBudgetExists"] = false;
        }
        if (!airlinesAccountData.contains("budgetEmployee"))
        {
            airlinesAccountData["budgetEmployee"] = 0;
        }
        if (!airlinesAccountData.contains("budgetCustomer"))
        {
            airlinesAccountData["budgetCustomer"] = 0;
        }
        if (!airlinesAccountData.contains("budgetPlaneCost"))
        {
            airlinesAccountData["budgetPlaneCost"] = 0;
        }
        if (!airlinesAccountData.contains("budgetCourier"))
        {
            airlinesAccountData["budgetCourier"] = 0;
        }
        if (!airlinesAccountData.contains("accountBalance"))
        {
            airlinesAccountData["accountBalance"] = 0;
        }

        employeeBudgetExists = airlinesAccountData["employeeBudgetExists"];
        passengerBudgetExists = airlinesAccountData["passengerBudgetExists"];
        planeCostBudgetExists = airlinesAccountData["planeCostBudgetExists"];
        courierBudgetExists = airlinesAccountData["courierBudgetExists"];

        budgetEmployee = airlinesAccountData["budgetEmployee"];
        budgetCustomer = airlinesAccountData["budgetCustomer"];
        budgetPlaneCost = airlinesAccountData["budgetPlaneCost"];
        budgetCourier = airlinesAccountData["budgetCourier"];

        accountBalance = airlinesAccountData["accountBalance"];
    }
    else
    {
        cout << "airlinesAccount.json doesn't exist!" << endl;
        return;
    }
}
