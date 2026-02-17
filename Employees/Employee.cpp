#include "Employee.h"

// Default constructor
Employee ::Employee() : User("None", "None", "None", "None"), department{"None"}, designation{"None"}, account{nullptr}, salary(), attendanceRecord(), presents(0), absents(0)
{
}

// Overloaded constructor
Employee ::Employee(const std::string &_firstName,
                    const std::string &_lastName,
                    const std::string &_id,
                    const std::string &_pass,
                    const std::string &_dep,
                    const std::string &_des,
                    Account *_acc,
                    const Salary &_sal)
    : User(_firstName, _lastName, _id, _pass), department(_dep), designation(_des), account(_acc), salary(_sal), attendanceRecord(), presents(0), absents(0)
{
}

// Getters
double Employee ::getSalary() const
{
  return this->salary.getBasicSalary();
}
std::string Employee ::getDesignation() const
{
  return designation;
}
std::string Employee ::getDepartment() const
{
  return department;
}
std::string Employee ::getAccountNumber() const
{
  return this->account->getAccountNumber();
}
double Employee ::getBalance() const
{
  return this->account->getBalance();
}
double Employee ::getBasicSalary() const
{
  return this->salary.getBasicSalary();
}
double Employee ::getAllowances() const
{
  return this->salary.getAllowances();
}
double Employee ::getDeductions() const
{
  return this->salary.getDeductions();
}
double Employee ::getHourlySalary() const
{
  return this->salary.getHourlySalary();
}
int Employee ::getAttendanceRecordSize() const
{
  return this->attendanceRecord.size();
}
int Employee :: getPresents () const
{
  return presents;
}
int Employee :: getAbsents () const
{
  return absents;
}

// Setters
void Employee ::setSalary(double sal)
{
  this->salary.setBasicSalary(sal);
}
void Employee ::setDepartment(std::string &dep)
{
  this->department = dep;
}
void Employee ::setDesignation(std::string &des)
{
  this->designation = des;
}
void Employee ::setAccountNumber(string num)
{
  this->account->setAccountNumber(num);
}
void Employee ::setBalance(double bal)
{
  this->account->setBalance(bal);
}

void Employee ::deposit(double amount)
{
  this->account->addBalance(amount, "Employees");
}

void Employee ::viewAttendanceRecord()
{
  readAttendanceFile();
  std::cout << "\nHi " << firstName << "! " << std::endl;
  std::cout << "\nFollowing is your attendance record:" << std::endl;
  std::cout << "Absents : " << absents << std::endl;
  std::cout << "Presents: " << presents << std::endl;

  std::cout << "______________________________________________" << std::endl;
  for (const auto &att : attendanceRecord)
  {
    att.display();
    std::cout << "______________________________________________" << std::endl;
  }
}

void Employee :: readAttendanceFile()
{
  json_attendance.clear();
  attendanceRecord.clear();
  absents = 0;
  presents = 0;

  // reading attendance file here !
  // Samer Path
  // std::string filePath = "Attendance\\"  + this->id + ".json";
  // Ahmad Absolute Path
//  std::string filePath = "C:\\Users\\User\\OneDrive\\Desktop\\PROJECT\\2024-Spring-SE102TB-Project-se102b-e\\Attendance\\" + this->id + ".json";
  string filePath = "C:\\OOPS_PROJECT_EXTENDED\\2024-Spring-SE102TB-Project-se102b-e\\Attendance\\" + this->id + ".json";
  std::ifstream readAttendanceFile(filePath, std::ios::in);

  try
  {
    if (!readAttendanceFile.is_open())
      throw std::runtime_error{"Could not open the attendance file -> " + this->id + ".json"};

    readAttendanceFile >> json_attendance;
    readAttendanceFile.close();
    for (int i = 0; i < json_attendance["Attendance"].size(); i++)
    {
      std::time_t a = json_attendance["Attendance"][i]["arrivalTime"];
      std::time_t d = json_attendance["Attendance"][i]["departureTime"];

      if (a == d)
        absents += 1;
      else
        presents++;

      Attendance attendance(a, d);
      attendanceRecord.push_back(attendance);
    }
  }
  catch (exception &ex)
  {
    std::cerr << "Exception: " << ex.what() << std::endl;
    sleep(3);
  }
  catch (...)
  {
    std::cerr << "Exception -> unknown! " << std::endl;
    sleep(3);
  }
}

void Employee ::updateAttendanceFile(void)
{
  // std::string filePath = "Attendance\\"  + this->id + ".json";   // SAMER,S PATH
  // Ahmad absolute path
  // std::string filePath = "Employees\\Attendance\\" + this->id + ".json";
//  std::string filePath = "C:\\Users\\User\\OneDrive\\Desktop\\PROJECT\\2024-Spring-SE102TB-Project-se102b-e\\Attendance\\" + this->id + ".json";
  string filePath = "C:\\OOPS_PROJECT_EXTENDED\\2024-Spring-SE102TB-Project-se102b-e\\Attendance\\" + this->id + ".json";
  std::ofstream update(filePath, std::ios::out);
  try
  {
    if (!update.is_open())
      throw std::runtime_error{"Could not open the attendance file -> " + this->id + ".json"};

    update << std::setw(4) << json_attendance << std::endl;
    update.close();
  }
  catch (exception &ex)
  {
    std::cerr << "Exception: " << ex.what() << std::endl;
    sleep(3);
  }
  catch (...)
  {
    std::cerr << "Exception -> unknown! " << std::endl;
    sleep(3);
  }
}

void Employee :: markAttendance(time_t &arrival, time_t &departure)
{
  readAttendanceFile();
  json j =
      {
          {"arrivalTime", arrival},
          {"departureTime", departure}};
  json_attendance["Attendance"].push_back(j);
  Attendance *attendance = new Attendance(arrival, departure);
  if (arrival == departure)
  {
    absents++;
  }
  else
  {
    presents++;
  }
  attendanceRecord.push_back(*attendance);
  updateAttendanceFile();
  delete attendance;
}

// Login Function
bool Employee ::login(const std::string &u_name, const std::string &pass) const
{
  if (this->id == u_name && this->pass == pass)
    return true;
  else
    return false;
}


double Employee :: calculateAttendancePercentage() 
{
    readAttendanceFile();
    if (attendanceRecord.empty()) // throw exception 
        throw 0;
    return static_cast<double>(presents)*100.0/(attendanceRecord.size());
}

