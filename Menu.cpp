#include "Menu.h"

void Menu()
{
    char choice;
    do
    {
      Airlines ::getInstance();

        system("clear");
        std ::cout << "\n\t\t  * * * * AIRLINES MANAGEMENT SYSTEM * * * *" << std::endl;
        std ::cout << "\n\t\t  A = Admin  "
                   << "\n\t\t  E = Employee "
                   << "\n\t\t  C = Customer  "
                   << "\n\t\t  D = Cargo  "
                   << "\n\t\t  Q = Quit " << std::endl;

        std::cout << "\n Enter choice: ";
        std::cin >> choice;

        switch (tolower(choice))
        {
        case 'a':
        {
            // Admin Controls
            std::string id, pass;
            std::cout << "\n\t\t Login to your account " << std::endl;
            std::cout << "\nEnter your Id  : ";
            std::cin >> id;
            std::cout << "Enter your pass: ";
            std::cin >> pass;
            Admin admin;
            if (admin.login(id, pass)) // Login check
            {
                std::cout << "\nLogged in successfully ! " << std::endl;
                std::cout << "\nLoading ......" << std::endl;
                sleep(3);
                char c;
                do
                {
                    system("clear");
                    std::cout << "\n\t\t * * * ADMIN CONTROL PANEL * * * " << std::endl;
                    std::cout << "\n\t\t E = Employee Management " << std::endl;
                    std::cout << "\t\t P = Purchase Airplanes " << std::endl;
                    std::cout << "\t\t V = View Airplanes " << std::endl;
                    std::cout << "\t\t B = Budget Management " << std::endl;
                    std::cout << "\t\t F = Flight department Management " << std::endl;
                    std::cout << "\t\t Q = Quit " << std::endl;
                    std::cout << "\nEnter choice: ";
                    std::cin >> c;

                    switch (tolower(c))
                    {
                    case 'e':
                    {
                        char c1;
                        do
                        {
                            system("clear");
                            std::cout << "\n\t\t\t * * * * EMPLOYEES MANAGEMENT * * * * " << std::endl;
                            std::cout << "\n\t\t A = Add Employee " << std::endl;
                            std::cout << "\t\t R = Delete Employee " << std::endl;
                            std::cout << "\t\t U = Update Employee " << std::endl;
                            std::cout << "\t\t D = Display Employees " << std::endl;
                            std::cout << "\t\t M = Mark Employees Attendance " << std::endl;
                            std::cout << "\t\t Q = Quit " << std::endl;
                            std::cin >> c1;
                            switch (tolower(c1))
                            {
                                case 'a':
                                {
                                    admin.addEmployee();
                                    break;
                                }
                                case 'r':
                                {
                                    admin.removeEmployee();
                                    break;
                                }
                                case 'u':
                                {
                                    admin.updateEmployee();
                                    break;
                                }
                                case 'd':
                                {
                                    admin.displayEmployees();
                                    break;
                                }
                                case 'm':
                                {
                                    admin.markAttendance();
                                    break;
                                }
                                case 'q':
                                {
                                    std::cout << "\nExiting Employee Management Panel......... " << std::endl;
                                    sleep (2);
                                    break;
                                }
                                default:
                                {
                                    std::cout << "\nInvalid choice! " << std::endl;
                                    continue;
                                }
                            }
                        } while (c1 != 'q');
                        break;
                    }
                    case 'p':
                    {
                        Airlines ::getInstance()->purchaseAirplanes();
                        break;
                    }
                    case 'v':
                    {
                        Airlines ::getInstance()->displayAirplanes();
                        sleep(2);
                        break;
                    }
                    case 'b': // Budget Handling !  
                    {      
                        
                        
                        char budgetChoice;
                        do
                        {
                            system ("clear");
                            std::cout << "\n\t\t S = Set Budget " << std::endl;
                            std::cout << "\n\t\t V = View Financial Reports " << std::endl;
                            std::cout << "\n\t\t A = Airlines Account Balance " << std::endl;
                            std::cout << "\n\t\t Q = Quit " << std::endl;
                            std::cin >> budgetChoice;

                            switch (tolower(budgetChoice))
                            {
                                case 's':
                                {   
                                    admin.setBudget();
                                    break;
                                }
                                case 'v':
                                {   
                                    cout << "[1]View Revenue Report, [2]View Transactions, [3]Set Airlines Balance: ";
                                    int ch;
                                    cin >> ch;
                                    if(ch == 1){
                                        admin.financialManagement();
                                    }
                                    if(ch == 2){
                                        admin.viewTransactionReport();
                                    }
                                    if(ch == 3){
                                        cout << "Current Balance: " << endl;
                                        admin.viewAirlinesBalance();
                                        cout << "How Much Balance To Set: ";
                                        double newBalance;
                                        cin >> newBalance;
                                        cout << endl;
                                        admin.setAirlinesBalance(newBalance);
                                    }
                                    
                                    break;
                                }
                                case 'a':
                                {
                                    admin.viewAirlinesBalance();
                                    break;
                                }
                                case 'q':
                                {
                                    std::cout << "\nExiting........." << std::endl;
                                    break;
                                }
                                default :
                                {
                                    std::cout << "\nnvalid choice! " << std::endl;
                                    continue;
                                }
                            }
                        }while (budgetChoice != 'q');
                        break;
                    }
                    case 'f':
                    {
                        Airlines::getInstance()->flightDepartmentAdminEnd();
                        break;
                    }
                    case 'q':
                    {
                        std::cout << "Exiting admin panel......" << std::endl;
                        break;
                    }
                    default:
                    {
                        std::cout << "\n Invalid Input! " << std::endl;
                        continue;
                    }
                }
                }while (c != 'q');
            }
            else
            {
                std::cout << "\nWrong credentials! " << std::endl;
                sleep(2);
            }
            break;
        }
        case 'c':
        {
            // Customer Controls
            std::cout << "\n\t\t * * * CUSTOMER CONTROL PANEL * * *" << std::endl;
            Airlines ::getInstance()->customerEnd();
            break;
        }
        case 'e': // Employee Controls
        {
            std::cout << "\n\t\t * * * EMPLOYEE CONTROL PANEL * * *" << std::endl;
            Airlines ::getInstance()->employeeEnd();
            break;
        }
        case 'd':
        {
            Airlines ::getInstance()->setCourier();
            break;
        }
        case 'q': // Quit
        {
            std::cout << "\n Exiting the program. Bye bye! \n";
            break;
        }
        default:
        {
            std::cout << "Invlalid choice. Try Again! " << std::endl;
            continue;
        }
        }
    } while (choice != 'Q' && choice != 'q');
}
