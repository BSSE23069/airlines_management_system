#include "Airlines.h"

Airlines ::Airlines() :flightDepartment (airplane,customers),airplaneMaintenance (airplane, employees)
{
    // Reading Airplane file!

    Company * company = Company ::getCompany();
    company->readPlanesFile(airplane);
    flightDepartment.readFlights();
    // Reading customers file!
    // Company *company= Company::getCompany();
    //company->readPlanesFile(airplane);
    
    
    std::ifstream readCustomers("Customers\\customers.json", std::ios::in);
    if (readCustomers.is_open()) {
        readCustomers >> json_customer;
        readCustomers.close();

        for (int i = 0; i < json_customer["Customers"].size(); i++) {
            std::string first = json_customer["Customers"][i]["firstName"];
            std::string last = json_customer["Customers"][i]["lastName"];
            std::string id = json_customer["Customers"][i]["id"];
            std::string pass = json_customer["Customers"][i]["pass"];
            customers.push_back(new Customer(first, last, id, pass));
        }
    } else {
        std::cerr << "Error opening the customers file!" << std::endl;
    }
    // Reading all the employees files!
    auto readEmployeeFile = [&](const std::string &filePath, const std::string &employeeType, json &j) {
        std::ifstream readEmployees(filePath, std::ios::in);
        if (readEmployees.is_open()) {
            readEmployees >> j;
            readEmployees.close();
            for (const auto &employee: j[employeeType]) {
                std::string first = employee["firstName"];
                std::string last = employee["lastName"];
                std::string id = employee["id"];
                std::string pass = employee["pass"];
                std::string dep = employee["department"];
                std::string des = employee["designation"];

                std::string accountNo = employee["account"]["accountNo"];
                double balance = employee["account"]["balance"];
                Account *account = new Account();
                account->setAccountNumber(accountNo);
                account->setBalance(balance);

                double basicSalary = employee["salary"]["basicSalary"];
                double allowances = employee["salary"]["allowances"];
                double deductions = employee["salary"]["deductions"];
                double hourlyRate = employee["salary"]["hourlySalary"];
                Salary salary(basicSalary, allowances, hourlyRate, deductions);

                if (employeeType == "Pilot") 
                {
                    double experience = employee["experience"];
                    employees.push_back(new Pilot(first, last, id, pass, dep, des, account, salary, experience));
                } 
                else if (employeeType == "FlightAttendant") 
                {
                    employees.push_back(new FlightAttendant(first, last, id, pass, dep, des, account, salary));
                }
                else if (employeeType == "Medic") 
                {
                    employees.push_back(new Medic(first, last, id, pass, dep, des, account, salary));
                }
                else if (employeeType == "InspectionManager")
                {
                   int inspections = employee["inspections"];
                   employees.push_back(new InspectionManager(first, last, id, pass, dep, des, account, salary, inspections));
                }
                else if (employeeType == "Technician")
                {
                   int tier = employee["tier"];
                   employees.push_back(new Technician(first, last, id, pass, dep, des, account, salary, tier));
                }
                else if (employeeType == "InspectionManager")
                {
                   int inspections = employee["inspections"];
                   employees.push_back(new InspectionManager(first, last, id, pass, dep, des, account, salary, inspections));
                }
                else if (employeeType == "Technician")
                {
                   int tier = employee["tier"];
                   employees.push_back(new Technician(first, last, id, pass, dep, des, account, salary, tier));
                }
            }
        } 
        else 
        {

            std::cerr << "Error opening the " << employeeType << " file!" << std::endl;
        }
    };
    readEmployeeFile("Employees\\pilots.json", "Pilot", json_pilots);
    readEmployeeFile("Employees\\medics.json", "Medic", json_medics);
    readEmployeeFile("Employees\\flightAttendants.json", "FlightAttendant", json_flightAttendants);
    readEmployeeFile("Employees\\inspectionManagers.json", "InspectionManager", json_inspectionManagers);
    readEmployeeFile("Employees\\technicians.json", "Technician", json_technicians);
}

Airlines *Airlines::getInstance() {
    static Airlines *instance = new Airlines;
    return instance;
}

bool Airlines::addCustomer(Customer *customer) {
    customers.push_back(customer);
    updateCustomersFile();
    return true;
}

void Airlines::updateCustomersFile() {
    json_customer["Customers"].clear();

    // Converting the vector back to json notation
    for (const auto &c: customers) {
        json j ={
        {"firstName", c->getFirstName()},
        {"lastName",  c->getLastName()},
        {"id",        c->getId()},
        {"pass",      c->getPass()}};
        json_customer["Customers"].push_back(j);
    }
    std::ofstream writeCustomers("Customers/customers.json", std::ios::out);
    if (writeCustomers.is_open()) {
        writeCustomers << std::setw(4) << json_customer << std::endl;
    } else {
        std::cerr << "Error opening the file ! " << std::endl;
    }
}

void Airlines :: customerEnd() 
{
    char choice;
    do {
        std::cout << "\n\t L = Login \n\t S = SignUp \n\t Q = Quit " << std::endl;
        std::cin >> choice;
        
        switch (tolower(choice)) {
            case 'l': {
                std::string userName, pass;

                std::cout << "\nEnter your username: ";
                std::cin >> userName;
                std::cout << "Enter your password: ";
                std::cin.ignore();
                getline(std::cin,pass);

                bool loggedIn = false;
                for (int i = 0; i < customers.size(); i++) {
                    if (customers.at(i)->login(userName, pass)) {
                        std::cout << "Logged In successfully ! " << std::endl;
                        loggedIn = true;
                        // Company::getCompany()->purchaseAirPlane(airplane);
//                        flightDepartment.addFlight();
                        flightDepartment.addPassengers(i);
                        sleep(3);
                        break;
                    }
                }
                if (!loggedIn)
                {
                    std::cout << "Wrong username or password. Please try again." << std::endl;
                }
                break;
            }
            case 's': 
            {
                signUp();
                break;
            }
            case 'q': 
            {
                std::cout << "Exiting the customer end........" << std::endl;
                sleep(3);
                break;
            }
            default: 
            {
                std::cout << "\nInvalid choice ! " << std::endl;
                continue;
            }
        }
    } while (choice != 'q' && choice != 'Q');
}    


void Airlines::signUp() {
    std::string firstName, lastName, id, pass, retypePass;

    std::cout << "Enter your first name: ";
    std::cin >> firstName;
    std::cout << "Enter your last  name: ";
    std::cin >> lastName;

    bool isUniqueId = false;
    do // User id should be unique
    {
        std::cout << "Enter your user Id   : ";
        std::cin >> id;

        bool idTaken = false;
        for (auto it = customers.begin(); it != customers.end(); ++it) {
            if (id == (*it)->getId()) {
                idTaken = true;
                std::cout << "This Id has already been taken. Try another one!\n";
                break;
            }
        }
        if (!idTaken) 
            isUniqueId = true;
    } while (!isUniqueId);

    do // Password
    {
        std::cout << "Enter your password (atleast 8 characters long) : ";
        getline(std::cin, pass);
        if (pass.length() < 8) {
            std::cout << "Weak password. Must be 8 characters long! " << std::endl;
        }
    } while (pass.length() < 8);

    do // Confirm password
    {
        std::cout << "Confirm password : ";
        getline(std::cin, retypePass);
        if (pass != retypePass) {
            std::cout << "Password does not match. Try again!" << std::endl;
        }
    } while (pass != retypePass);

    Customer temp(firstName, lastName, id, pass);
    if (addCustomer(&temp)) 
    {
        std::cout << " Signed Up successfully! " << std::endl;
        return;
    } 
    else 
    {
        std::cout << " Error singning in. " << std::endl;
        return;
    }
}

void Airlines::displayCustomers() const {
    for (int i = 0; i < customers.size(); i++) {
        std::cout << " Customer " << i + 1 << " details " << std::endl;
        customers.at(i)->displayInfo();
    }
}


// Employees End Functionalities
void Airlines::employeeEnd() {
    std::string id, pass;

    std::cout << "\nEnter your employee Id: ";
    std::cin >> id;
    std::cout << "\nEnter your password   : ";
    std::cin >> pass;

    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if ((*it)->login(id, pass)) {
            std::cout << "\nLogged in successfully !" << std::endl;
            std::cout << "Loading menu ........ " << std::endl;
            sleep(3);
            displayEmployeeMenu(*it);
            return;
        }
    }
    std::cout << "Invalid credentials. Please try again." << std::endl;
}

void Airlines::displayEmployeeMenu(Employee *emp) {
    char choice;
    do {
        system("clear");
        std::cout << "\n\t\t* * * EMPLOYEES MENU * * * " << std::endl;
        std::cout << "\n\t V = View Attendance Record " << std::endl;
        std::cout << "\n\t P = Attendance Percentage " << std::endl;
        std::cout << "\n\t D = Display my Bio-Data " << std::endl;
        if(emp->getDesignation() == "InspectionManager")
            std::cout << "\n\t M = Airplane Maintenance Panel" << std::endl;
        std::cout << "\n\t Q = Quit " << std::endl;  
        std::cin >> choice;  

        switch (choice) {
            case 'v': // Attendance record
            case 'V': 
            {
                emp->viewAttendanceRecord();
                sleep(10);
                break;
            }
            case 'P': // Attendance percentage
            case 'p': 
            {   
                time_t now = time (nullptr);
                struct tm* date  = std :: localtime (&now); 
                char buff [15];
                strftime (buff, 15, "%B", date); // for month
                std::cout << "\n\t\t YOUR ATTENDANCE PERCENTAGE FOR " << buff << " " << 1900+date->tm_year << " is following: " << std::endl;
                try 
                {
                    double percentage = emp->calculateAttendancePercentage();
                    std::cout << "Attendance Percentage : " << percentage << " % " << std::endl;
                    std::cout << "Total Presents : " << emp->getPresents() << std::endl;
                    std::cout << "Total Absents  : " << emp->getAbsents() << std::endl;
                    sleep(5);
                }
                catch (int& ex)
                {
                    std::cerr << "Exception: Division by zero! " << std::endl;
                    sleep(2);
                }
                break;
            }
            case 'd': // Bio-data
            case 'D': 
            {
                emp->displayInfo();
                sleep(10);
                break;
            }
            case 'm':
            case 'M':
            {
                airplaneMaintenance.maintenanceMenu();
                break;
            }
            case 'q': // Exit
            case 'Q': 
            {
                std::cout << "\n Exiting the menu. Have a nice day!" << std::endl;
                sleep(3);
                break;
            }
            default: {
                std::cout << "\n Invalid choice! " << std::endl;
                continue;
            }
        }
    } while (choice != 'q' && choice != 'Q');
}


bool Airlines::isUniqueEmployeeId(const std::string &id) {
    for (const auto &emp: employees) {
        if (emp->getId() == id)
            return true;
    }
    return false;
}

void Airlines ::purchaseAirplanes() {

    Company ::getCompany()->purchaseAirPlane(airplane);
}

void Airlines ::displayAirplanes() {

    for (int i = 0; i < airplane.size(); ++i) {
      if(airplane[i].isPlaneAvailable())
            cout << "[" << i + 1 << "] " << airplane[i].getPlaneID() << endl;
      else
            cout << "[" << i + 1 << "] " << airplane[i].getPlaneID() << "  ** UNAVAILABLE **  " << endl;
    }
}

bool Airlines :: addEmployee(Employee *employee)
{
    employees.emplace_back(employee);
        // Converting the employee to JSON notation !
        json emp = {
                {"firstName",   employee->getFirstName()},
                {"lastName",    employee->getLastName()},
                {"id",          employee->getId()},
                {"pass",        employee->getPass()},
                {"department",  employee->getDepartment()},
                {"designation", employee->getDesignation()},
                {"account",
                { 
                        {"accountNo",   employee->getAccountNumber()},
                        {"balance",    employee->getBalance()}}},
                {"salary",
                {
                        {"basicSalary", employee->getBasicSalary()},
                        {"allowances", employee->getAllowances()},
                        {"hourlySalary", employee->getHourlySalary()},
                        {"deductions", employee->getDeductions()}}}};

        const std::type_info &type = typeid(*employee);
        std::string typeName = type.name();

        if (typeName == typeid(Pilot).name()) 
        {
            Pilot *pilot = dynamic_cast<Pilot *>(employee);
            emp["experience"] = pilot->getExperience();
            json_pilots["Pilot"].push_back(emp);
            updateEmployeesFile("Employees/pilots.json", "Pilot");
        } 
        else if (typeName == typeid(FlightAttendant).name()) 
        {
            json_flightAttendants["FlightAttendant"].push_back(emp);
            updateEmployeesFile("Employees/flightAttendants.json", "FlightAttendant");
        } 
        else if (typeName == typeid(Medic).name()) 
        {
            json_medics["Medic"].push_back(emp);
            updateEmployeesFile("Employees/medics.json", "Medic");
        }
        else if (typeName == typeid(InspectionManager).name())
        {
            InspectionManager *inspectionManager = dynamic_cast<InspectionManager *>(employee);
            emp["inspections"] = inspectionManager->getInspections();
            json_inspectionManagers["InspectionManager"].push_back(emp);
            updateEmployeesFile("Employees/inspectionManagers.json", "InspectionManager");
        }
        else if (typeName == typeid(Technician).name())
        {
            Technician *technician = dynamic_cast<Technician *>(employee);
            emp["tier"] = technician->getTier();
            json_technicians["Technician"].push_back(emp);
            updateEmployeesFile("Employees/technicians.json", "Technician");
        }

        // Create attendance file
        json data;
        json attendance = json::array();
        data["Attendance"] = attendance;
        std::ofstream createAttendanceFile("Attendance/" + employee->getId() + ".json", std::ios::out);
        createAttendanceFile << std::setw(4) << data << std::endl;
        createAttendanceFile.close();
        return true;
}

bool Airlines :: removeEmployee(const std::string &id) {
    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if (id == (*it)->getId()) {
            const type_info &type = typeid(**it);
            employees.erase(it);  // Erase the employee from the vector first 


            if (typeid(Pilot).name() == type.name()) {
                auto &pilotArray = json_pilots["Pilot"];
                for (auto it = pilotArray.begin(); it != pilotArray.end(); ++it) {
                    if ((*it)["id"] == id) {
                        pilotArray.erase(it);
                        break;
                    }
                }
                updateEmployeesFile("Employees\\pilots.json", "Pilot");
            }
            else if (typeid(FlightAttendant).name() == type.name())
            {
                auto &flightAttendantArray = json_flightAttendants["FlightAttendant"];
                for (auto it = flightAttendantArray.begin(); it != flightAttendantArray.end(); ++it) {
                    if ((*it)["id"] == id) {
                        flightAttendantArray.erase(it);
                        break;
                    }
                }
                updateEmployeesFile("Employees\\flightAttendants.json", "FlightAttendant");
            }
            else if (typeid(Medic).name() == type.name())
            {
                auto &medicArray = json_medics["Medic"];
                for (auto it = medicArray.begin(); it != medicArray.end(); ++it) {
                    if ((*it)["id"] == id) {
                        medicArray.erase(it);
                        break;
                    }
                }
                updateEmployeesFile("Employees\\medics.json", "Medic");
            }
            else if (typeid(InspectionManager).name() == type.name())
            {
                auto &inspectionManagerArray = json_inspectionManagers["InspectionManager"];
                for (auto it = inspectionManagerArray.begin(); it != inspectionManagerArray.end(); ++it)
                {
                    if ((*it)["id"] == id)
                    {
                        inspectionManagerArray.erase(it);
                        break;
                    }
                }
                updateEmployeesFile("Employees\\inspectionManagers.json", "InspectionManager");
            }
            else if (typeid(Technician).name() == type.name())
            {
                auto &technicianArray = json_technicians["Technician"];
                for (auto it = technicianArray.begin(); it != technicianArray.end(); ++it)
                {
                    if ((*it)["id"] == id)
                    {
                        technicianArray.erase(it);
                        break;
                    }
                }
                updateEmployeesFile("Employees\\technicians.json", "Technician");
            }
            return true;
        }
    }
    return false;
}

void Airlines :: updateEmployeesFile(const std::string &filePath, const std::string &typeName) 
{
    ofstream update(filePath, std::ios::out);
    if (!update.is_open())
        throw std::runtime_error{"Could not update the file -> " + filePath};

    if (typeName == "Pilot") 
    {
        update << std::setw(4) << json_pilots << std::endl;
    } 
    else if (typeName == "FlightAttendant") 
    {
        update << std::setw(4) << json_flightAttendants << std::endl;
    } 
    else if (typeName == "Medic") 
    {
        update << std::setw(4) << json_medics << std::endl;
    }
    else if (typeName == "InspectionManager")
    {
        update << std::setw(4) << json_inspectionManagers << std::endl;
    }
    else if (typeName == "Technician")
    {
        update << std::setw(4) << json_technicians << std::endl;
    }
    /*
    We can handle as many cases here !
    */
    update.close();
}

void Airlines :: displayEmployees() const {
    char choice;
    do {
        system("clear");
        std::cout << "\n\t\t P = Display Pilots only" << std::endl;
        std::cout << "\n\t\t M = Display Medics only" << std::endl;
        std::cout << "\n\t\t F = Display Flight Attendants only" << std::endl;
        std::cout << "\n\t\t T = Display Technicians only" << std::endl;
        std::cout << "\n\t\t I = Display Inspection Managers only" << std::endl;
        std::cout << "\n\t\t A = Display All Employees" << std::endl;
        std::cout << "\n\t\t E = Exit" << std::endl;
        std::cin >> choice;

        switch (std::toupper(choice)) {
            case 'P': // Pilots
                displayByType<Pilot>("Pilot");
                break;
            case 'M': // Medics
                displayByType<Medic>("Medic");
                break;
            case 'F': // Flight Attendants
                displayByType<FlightAttendant>("Flight Attendant");
                break;
            case 'T': // Technicians
                displayByType<Technician>("Technician");
                break;
            case 'I': // Inspection Managers
                displayByType<InspectionManager>("Inspection Manager");
                break;
            case 'A': // All Employees
                displayAllEmployees();
                break;
            case 'E': // Exit
                std::cout << "\nExiting............" << std::endl;
                break;
            default:
                std::cout << "Invalid choice! " << std::endl;
                continue;
        }
    } while (std::toupper(choice) != 'E');
}


template <class T>
void Airlines :: displayByType (const std::string& typeName) const 
{
    std::cout << "\n\t\t" << typeName << " of the Airlines are following!" << std::endl;
    int count = 0;
    std::cout << "\n------------------------------------------------------------" << std::endl;
    for (int i = 0; i < employees.size(); ++i) {
        T* employee = dynamic_cast<T*>(employees[i]);
        if (employee) {
            std::cout << "\n" << typeName << " " << ++count << std::endl;
            employee->displayInfo();
            std::cout << "------------------------------------------------------------" << std::endl;
        }
    }
    sleep(7);
}

void Airlines :: displayAllEmployees() const {
    std::cout << "\n TOTAL EMPLOYEES OF AIRLINES ARE " << employees.size() << std::endl;
    int count = 0;
    std::cout << "\n------------------------------------------------------------" << std::endl;
    for (int i = 0; i < employees.size(); ++i) {
        std::cout << "Employee " << ++count << std::endl;
        employees[i]->displayInfo();
        std::cout << "\n------------------------------------------------------------" << std::endl;
    }
    sleep (7);
}

bool Airlines :: isAttendanceMarkedForToday ()
{
    std::ifstream check ("Attendance\\isAttendanceMarked.json", std::ios::in);
    json data;

        if (!check.is_open())
            throw std::runtime_error {"Could not open the file -> isAttendanceMarked.json"};
        check >> data;
        check.close();  

        time_t now = time (nullptr);
        struct tm* currTime = localtime (&now);

            int year = currTime->tm_year;
            int month = currTime->tm_mon;
            int monthDay = currTime->tm_mday;

        if (data["year"] == year && data["month"] == month && data["monthDay"] == monthDay)
            return true;
        else 
            return false;  
}
    
void Airlines :: markAttendance() 
{
    try 
    {
        if (isAttendanceMarkedForToday())
        {
            std::cout << "\nAttendance for today has already been marked! " << std::endl;
            sleep(3);
            return;
        } 
    }
    catch (exception& ex)
    {
        std::cerr << "\nException: " << ex.what() << std::endl;
        sleep (3);
    }
    catch(...)
    {
        std::cerr << "\nUnknown exception occured! " << std::endl;
        sleep (3);
    }

    time_t now = time(nullptr);
    std::tm *timeinfo = std::localtime(&now);
    char buffer[80];
    std::strftime(buffer, 80, "%Y-%m-%d", timeinfo);

     // Write to the the file that today,s attendance has been done!
        ofstream attendanceMarkedToday ("Attendance\\isAttendanceMarked.json", std::ios::out);
        try 
        {
            if (!attendanceMarkedToday.is_open())
                throw std::runtime_error {"Could not open the file -> isAttendanceMarked.json"};
                json j = 
                {
                    {
                        "year", timeinfo->tm_year
                    },
                    {
                        "month", timeinfo->tm_mon
                    },
                    {
                        "monthDay", timeinfo->tm_mday
                    }
                };
                attendanceMarkedToday << std::setw(4) << j << std::endl;
                attendanceMarkedToday.close();
        }
        catch (exception& ex)
        {
            std::cerr << "Exception: " << ex.what () << std::endl;
            sleep(3);
        }
        catch (...)
        {
            std::cerr << "Exception: " << " unknown! " << std::endl;
            sleep(3);
        }
 
// Now mark attendance here ! 
    char status;
    for (auto &emp: employees) 
    {
        system("clear");
        std::cout << "\n\n\t\t[ Mark Attendance For Today => " << buffer << " ]" << std::endl;
        std::cout << emp->getId() << " Attendance Turn. " << std::endl;
        std::cout << "\n\t [A] = Absent " << "\n\t [P] = Present \n\t [Q] = Quit " << std::endl;
        std::cout << "Enter: ";
        std::cin >> status;

        switch (tolower(status)) 
        {
            case 'a': // Absent case
            {
                time_t t = time(nullptr);
                emp->markAttendance(t, t);
                std::cout << "\n Absent marked for " << emp->getFirstName() << std::endl;
                sleep(2);
                break;
            }
            case 'p': // Present case
            {
                std::tm a = {}, d = {};
                std::string a_str, d_str;
                int start, end;
                do
                {
                    std::cin.ignore();              
                    std::cout << "\n Enter arrival time -> format  [YYYY-MM-DD HH:MM:SS]  : ";
                    getline(std::cin, a_str);
                    start = sscanf(a_str.c_str(), "%d-%d-%d %d:%d:%d", &a.tm_year, &a.tm_mon, &a.tm_mday, &a.tm_hour,
                                   &a.tm_min, &a.tm_sec);
                    if (start != 6 || !is_valid_tm(a))
                        std::cout << "Wrong format or invalid date. Try again [YYYY-MM-DD HH:MM:SS] !" << std::endl;

                } while (start != 6 || !is_valid_tm(a));

                a.tm_year -= 1900; // For proper year
                a.tm_mon--;        // (0-11)
                std::time_t time_t_arrival = std::mktime(&a);
                if (time_t_arrival == -1) {
                    std::cout << "Invalid date and time values! " << std::endl;
                    sleep(2);
                    return;
                }
                do 
                {
                    std::cout << "\n Enter departure time -> format [YYYY-MM-DD HH:MM:SS] : ";
                    getline(std::cin, d_str);
                    end = sscanf(d_str.c_str(), "%d-%d-%d %d:%d:%d", &d.tm_year, &d.tm_mon, &d.tm_mday, &d.tm_hour,
                                 &d.tm_min, &d.tm_sec);
                    if (end != 6 || !is_valid_tm(d))
                        std::cout << "Wrong format or invalid date. Try again [YYYY-MM-DD HH:MM:SS] !" << std::endl;
                } while (end != 6 || !is_valid_tm(d));

                d.tm_year -= 1900;
                d.tm_mon--;
                std::time_t time_t_departure = std::mktime(&d);
                if (time_t_departure == -1) {
                    std::cout << "Invalid date and time values! " << std::endl;
                    sleep(2);
                    return;
                }
                emp->markAttendance(time_t_arrival, time_t_departure);
                std::cout << "\n Present marked for " << emp->getId() << std::endl;
                sleep(2);
                break;
            }
            case 'q': // Quit 
            {
                std::cout << "\n Exiting........" << std::endl;
                sleep(2);
                break;
            }
            default: {
                std::cout << "\n Invalid status ! " << std::endl;
                continue;
            }
        }
    }
}


void Airlines :: transferSalary() 
{
    for (int i = 0; i < employees.size(); ++i) {

        employees.at(i)->readAttendanceFile();
        if (employees.at(i)->getAttendanceRecordSize() == 30) {
            double salary = employees.at(i)->calculateSalary();
            employees.at(i)->deposit(salary);
            // Hamare account me se salary minus
            break;
        }
    }
}

void Airlines::flightDepartmentAdminEnd(){
    flightDepartment.adminEnd(airplaneMaintenance);
}


bool is_valid_tm(const std::tm &t) {
    return (t.tm_year >= 0 && t.tm_mon >= 0 && t.tm_mon < 12 && t.tm_mday > 0 && t.tm_mday <= 31);
}

void Airlines ::setCourier() {

    Delivery d1;
    Courier* c1=Courier::getInstance();
    json cargoPLane;
    Sender s1;
    Receiver r1;
    Person *p1;
    json employee;
    json courier;
    int n=0;

    while (true) {
        cout << "enter 1 to send package|| enter 2 for  deliveryEmployee ||enter 3 for exit || enter 4 to record landed planes" << endl;
        cin>>n;
        if(n==1){
            int date;
            time_t now = time(nullptr);
            tm* ti = localtime(&now);
            date = ti->tm_mday;
//            p1=new Sender;
//            p1->PutInfo();
//            p1=new Receiver;
//            p1->PutInfo();

            c1->displayCargoPlanes(airplaneMaintenance,airplane) ;
            cout<<"assigning work to cargoPlane"<<endl;



        }
        if(n==2){
            int i=0;
            while(i!=4)
            {
                    cout<<"enter 1 for add employee  || enter 2 for remove employee || enter 3 for attendance || enter 4 for exit"<<endl;
                    cin>>i;
                    if(i==1){
                        c1->addEmployee(employee);
                    }
                    if(i==2){
                        c1->removeEmployee(employee);

                    }
                    if(i==3){
                        string employeeName;
                        int days;
                        time_t now = time(nullptr);
                        tm *ti = localtime(&now);
                        cout<<ti->tm_mday;
                        cout<<"enter name of employee: "<<endl;
                        cin>>employeeName;
                        cout<<"enter day "<<endl;
                        c1->attendance(employee,days,employeeName);
                        int year=ti->tm_year;
                        int month=ti->tm_mon;
                        c1->deductSalary(employee,year,month);
                    }
            }

        }
        if(n==3)
            break;
        if(n==4)
        {
            c1->endFlight(airplaneMaintenance, airplane);
            d1.assignWorkToEmployee();
        }

    }
}