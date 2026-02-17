#include "Admin.h"


// No-Args Constructors
Admin ::Admin() : Admin("Ahmad", "Khan", "admin", "admin")
{

    std::ifstream readAdmin;
    readAdmin.open("Employees\\admin.json");
    if (readAdmin.is_open())
    {
        json data;
        readAdmin >> data;
        this->firstName = data["firstName"];
        this->lastName = data["lastName"];
        this->id = data["id"];
        this->pass = data["pass"];
        readAdmin.close();
    }
    else
    {
        std::cerr << "Unable to open admin.json" << std::endl;
    }
}

Admin ::Admin(
    const std::string &first, // firstName
    const std::string &last,  // lastName
    const std::string &id,    // id
    const std::string &pass)  // pass
    : User(first, last, id, pass)
{
}

Admin ::~Admin()
{
}

// Customer functions
void Admin ::displayCustomers() const
{
    Airlines ::getInstance()->displayCustomers();
}

void Admin :: addEmployee()
{
    int choice;
    Employee *emp = nullptr;
    Employee *temp = nullptr;
    Account *account = nullptr;

    std::string first, last, id, pass, dep, des, accountNo; // common attributes
    double exp, balance, basicSalary, allowances, hourlyWage;
    int inspections, tier; // attributes unique to inspection_managers & technicians

    do
    {
        system("clear");
        std::cout << "\n\t\t Employee Type " << std::endl;
        std::cout << "\t 1) Pilot \n\t 2) Medic \n\t 3) Flight Attendant "
                     "\n\t 4) Inspection Manager \n\t 5) Technician \n\t 6) Exit"
                  << std::endl;
        std::cout << "\n Enter: ";
        std::cin >> choice;

        if (choice == 6)
            break;

        std::cin.ignore();
        std::cout << "\nEnter employee first name  : ";
        std::cin >> first;
        std::cout << "Enter employee last  name  : ";
        std::cin >> last;

        bool isUniqueId; // Checking if the id is unique or not
        do
        {
            std::cout << "Enter employee id          : ";
            std::cin >> id;
            isUniqueId = !Airlines::getInstance()->isUniqueEmployeeId(id);
            if (!isUniqueId)
            {
                std::cout << "Employee id " << id << " has already been taken!" << std::endl;
            }
        } while (!isUniqueId);

        std::cout << "Set employee pass          : ";
        std::cin >> pass;
        std::cout << "Enter employee department  : ";
        std::cin >> dep;
        std::cout << "Enter employee designation : ";
        std::cin >> des;
        std::cout << "\n\t Account Information " << std::endl;
        std::cout << "Set employee account no    : ";
        std::cin >> accountNo;
        std::cout << "Set employee balance       : ";
        std::cin >> balance;

        std::cout << "\n\t Salary Information " << std::endl;
        std::cout << "Set employee basic salary  : ";
        std::cin >> basicSalary;
        std::cout << "Set employee allowances    : ";
        std::cin >> allowances;
        std::cout << "Set employee hourly Wage   : ";
        std::cin >> hourlyWage;

        account = new Account();
        account->setAccountNumber(accountNo);
        account->setBalance(balance);
        Salary *salary = new Salary(basicSalary, allowances, hourlyWage);

        switch (choice)
        {
        case 1: // Pilot
        {
            std::cout << "Enter pilot experience: ";
            std::cin >> exp;
            emp = new Pilot(first, last, id, pass, dep, des, account, *salary, exp);
            try
            {
                if (!Airlines ::getInstance()->addEmployee(emp /*type*/))
                {
                    std::cout << "Could not add a pilot. " << std::endl;
                    sleep(2);
                }
                std::cout << "\nAdded a pilot sucessfully! " << std::endl;
                sleep(2);
            }
            catch (const std::runtime_error &ex)
            {
                std::cout << "Problem adding a new pilot: " << ex.what() << std::endl;
                sleep(3);
            }
            delete salary;
            break;
        }
        case 2: // Medic
        {
            emp = new Medic(first, last, id, pass, dep, des, account, *salary);
            try
            {
                if (!Airlines ::getInstance()->addEmployee(emp /*type*/))
                {
                    std::cout << "Could not add a medic. " << std::endl;
                    sleep(2);
                }
                std::cout << "\nAdded a Medic sucessfully! " << std::endl;
            }
            catch (const std::runtime_error &ex)
            {
                std::cout << "Problem adding a new medic: " << ex.what() << std::endl;
                sleep(3);
            }
            delete salary;
            break;
        }
        case 3: // Flight Attendant
        {
            emp = new FlightAttendant(first, last, id, pass, dep, des, account, *salary);
            try
            {
                if (!Airlines ::getInstance()->addEmployee(emp /*type*/))
                {
                    std::cout << "Could not add a flight attendant. " << std::endl;
                    sleep(2);
                }
                std::cout << "\nAdded a flight attendant sucessfully! " << std::endl;
            }
            catch (const std::runtime_error &ex)
            {
                std::cout << "Problem adding a new flight attendant: " << ex.what() << std::endl;
                sleep(3);
            }
            delete salary;
            break;
        }
        case 4: // Inspection Managers
        {
            std::cout << "Enter Inspection Manager inspections history : ";
            std::cin >> inspections;
            emp = new InspectionManager(first, last, id, pass, dep, des, account, *salary, inspections);
            try
            {
                if (!Airlines ::getInstance()->addEmployee(emp /*type*/))
                {
                    std::cout << "Could not add an inspection manager. " << std::endl;
                    sleep(2);
                }
                std::cout << "\nAdded an inspection manager sucessfully! " << std::endl;
                sleep(2);
            }
            catch (const std::runtime_error &ex)
            {
                std::cout << "Problem adding a new inspection manager: " << ex.what() << std::endl;
                sleep(3);
            }
            delete salary;
            break;
        }
        case 5: // Technicians
        {
            std::cout << "Enter Technician tier : ";
            std::cin >> tier;
            emp = new Technician(first, last, id, pass, dep, des, account, *salary, tier);
            try
            {
                if (!Airlines ::getInstance()->addEmployee(emp /*type*/))
                {
                    std::cout << "Could not add a technician. " << std::endl;
                    sleep(2);
                }
                std::cout << "\nAdded a technician sucessfully! " << std::endl;
                sleep (2);
            }
            catch (const std::runtime_error &ex)
            {
                std::cout << "Problem adding a new technician: " << ex.what() << std::endl;
                sleep(3);
            }
            delete salary;
            break;
        }
        case 6:
        {
            std::cout << "Exiting ....." << std::endl;
            break;
        }
        default:
        {
            std::cout << "Invalid choice! " << std::endl;
            continue;
        }
        }
    } while (choice != 6);

}

void Admin ::removeEmployee()
{
    std::string enterId;
    std::cout << "\n Enter employee Id to remove the employee: ";
    std::cin >> enterId;
    if (Airlines ::getInstance()->removeEmployee(enterId))
    {
        std::cout << "\n Employee with id " << enterId << " has been removed! " << std::endl;
        sleep (3);
        return;
    }
    else
    {
        std::cout << "\n Employee with id " << enterId << " was not found in record!" << std::endl;
        sleep (3);
        return;
    }
}

void Admin ::updateEmployee()
{
    std ::cout << "NULL" << std ::endl;
}

void Admin ::markAttendance()
{
    Airlines ::getInstance()->markAttendance();
}

void Admin ::transferSalary()
{
    Airlines ::getInstance()->transferSalary();
}

void Admin ::displayEmployees() const
{
    Airlines ::getInstance()->displayEmployees();
}

// Overriden functions
bool Admin ::login(const std::string &id, const std::string &pass) const
{
    if (this->id == id && this->pass == pass)
        return true;
    return false;
}

void Admin ::displayInfo() const
{
    std::cout << *this << std::endl;
}

// friend functions
std::ostream &operator<<(std::ostream &os, const Admin &admin)
{
    os << "> Admin first name      : " << admin.firstName << std::endl;
    os << "> Admin last name       : " << admin.lastName << std::endl;
    os << "> Admin Id              : " << admin.id << std::endl;
    os << "> Admin Password        : " << admin.pass << std::endl;
    return os;
}

void Admin :: setBudget(){
    AirlinesAccount::getInstance()->setBudget();
}
void Admin :: financialManagement(){
    AirlinesAccount::getInstance()->callRevenueMenu();
}
void Admin :: viewAirlinesBalance(){
    AirlinesAccount::getInstance()->loadAirlinesData();
    cout << "Current Airlines Balance " << AirlinesAccount::getInstance()->getAccountBalance() << endl;
}

void Admin :: viewTransactionReport(){
    AirlinesAccount::getInstance()->viewTransactionReport();
}

void Admin :: setAirlinesBalance(double balance){
    AirlinesAccount::getInstance()->setBalance(balance);
}