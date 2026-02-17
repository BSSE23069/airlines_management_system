#include "AccountsManagement.h"

// AccountsManagement* AccountsManagement::instance = 0;

// void AccountsManagement:: generateRevenueReport(){ //In this function we only generate the revenue, not overall profit

//     double revenue;
    
//     for (int i = 0; i < passengerAccounts.size(); i++)
//     {
//         revenue += passengerAccounts[i].fee; //Adding up the fee of all passengers
//     }

//     for (int i = 0; i < courierAccounts.size(); i++)
//     {
//         /* code */
//     }
    
//     }

    // string AccountsManagement:: verifyAccounts(string thatAccountNumber){
        

    //     for (int i = 0; i < employeeAccounts.size(); i++)
    //     {

    //         if(employeeAccounts[i].account.getAccountNumber() == thatAccountNumber){
    //             return thatAccountNumber;
    //         }
    //     }

    //     for (int i = 0; i < passengerAccounts.size(); i++)
    //     {
    //         if(passengerAccounts[i].account->getAccountNumber() == thatAccountNumber){
    //             return thatAccountNumber;
    //         }
    //     }

    //     for (int i = 0; i < planeCostsAccounts.size(); i++)
    //     {
    //         if(planeCostsAccounts[i].account->getAccountNumber() == thatAccountNumber){
    //             return thatAccountNumber;
    //         }
    //     }

    //     for (int i = 0; i < courierAccounts.size(); i++)
    //     {
    //         if(courierAccounts[i].account->getAccountNumber() == thatAccountNumber){
    //             return thatAccountNumber;
    //         }
    //     }

    //     //If loops complete and no account matches with the provided accountNumber then call some other function

    //     // cout << "Sorry, the account number doesn't exist in our data base!" << endl;

    // }

    // void AccountsManagement:: calculateRevenue(){ //Only calculating how much money the company is generating, ignoring the money lost

    //     double totalRevenue = 0; //Store the calculated revenue
    //     double passengerRevenue = 0;
    //     double courierRevenue = 0;
    //     time_t now = time(NULL);
    //     string stringNow = ctime(&now);

    //     for (int i = 0; i < passengerAccounts.size(); i++)
    //     {
    //         passengerRevenue += passengerAccounts[i].fee;
            
    //     }

    //      for (int i = 0; i < courierAccounts.size(); i++)
    //     {
    //         courierRevenue += passengerAccounts[i].fee;
            
    //     }

    //     totalRevenue = passengerRevenue + courierRevenue;

    //     ofstream out ("revenueReport.txt");
    //     out << "Date: " << stringNow << endl;
    //     out << "Total Revenue: " << totalRevenue << endl;
    //     out << "Revenue From Passenger Department: " << passengerRevenue << endl;
    //     out << "Revenue From Courier Department: " << courierRevenue << endl;
    //     out << "----------------------------------------------------------" << endl;

    // }
    // void AccountsManagement:: calculateLoss(){ //Only calculating how much money the company is spending, ignoring the money gained
    //     time_t now = time(NULL);
    //     string stringNow = ctime(&now);

    //     double totalRevenueLost = 0; //Store the calculated revenue
    //     double employeeRevenueLost = 0;
    //     double planeCostRevenueLost = 0;
        

    //     for (int i = 0; i < employeeAccounts.size(); i++)
    //     {
    //         employeeRevenueLost += employeeAccounts[i].salary;
            
    //     }

    //      for (int i = 0; i < planeCostsAccounts.size(); i++)
    //     {
    //         planeCostRevenueLost += planeCostsAccounts[i].cost;
            
    //     }

    //     totalRevenueLost = employeeRevenueLost + planeCostRevenueLost;

    //     ofstream out ("revenueReport.txt");
    //     out << "Date: " << stringNow << endl;
    //     out << "Total Money Lost: " << totalRevenueLost << endl;
    //     out << "Money Lost From Employee Department: " << employeeRevenueLost << endl;
    //     out << "Money Lost From Plane Costs Department: " << planeCostRevenueLost << endl;
    //     out << "----------------------------------------------------------" << endl;

    // }
    // void AccountsManagement:: calculateProfit(){ //Combining The Revenue Gained And Revenue Lost To Calculate Total Profit
    // time_t now = time(NULL);
    // string stringNow = ctime(&now);
    // //Revenue Lost
    // double totalRevenueLost = 0;

    // for (int i = 0; i < employeeAccounts.size(); i++)
    //     {
    //         totalRevenueLost += employeeAccounts[i].salary;
            
    //     }

    // for (int i = 0; i < planeCostsAccounts.size(); i++)
    //     {
    //         totalRevenueLost += planeCostsAccounts[i].cost;
            
    //     }

    

    // //Revenue Gained
    // double totalRevenueGained = 0;

    // for(int i=0; i<passengerAccounts.size(); i++){
    //     totalRevenueGained += passengerAccounts[i].fee;
    // }
    // for(int i=0; i<courierAccounts.size(); i++){
    //     totalRevenueGained += courierAccounts[i].fee;
    // }

    // double totalProfit = (totalRevenueGained - totalRevenueLost)/100;

    // ofstream out("profitReport.txt");
    // out << "Date: " << stringNow << endl;
    // out << "Profit: " << totalProfit << endl;
    // out << "----------------------------------" << endl;

    
    // }