#ifndef _AIRLINES_H_
#define _AIRLINES_H_

// Company Header
#include "Company/Company.h"
// Customer Header
#include "Customers/Customer.h"
// Employees Headers
#include "Employees/pilot.h"
#include "Employees/Medic.h"
#include "Employees/FlightAttendant.h"
#include "Employees/InspectionManager.h"
#include "Employees/Technician.h"
// Department Headers
#include "Departments/FlightDepartment.h"
#include "Departments/AirplaneMaintenance.h"
// Courier Headers
#include "cargoCompany/Courier.h"
#include "cargoCompany/Delivery.h"
#include "cargoCompany/Person.h"
#include "cargoCompany/Sender.h"
#include "cargoCompany/Receiver.h"
#include "cargoCompany/Address.h"
#include "cargoCompany/Items.h"

class Airlines // Singleton class 
{
private:
   std::vector<Customer*> customers;        // Aggregated
   std::vector<Employee*> employees;        // Aggregated
   std::vector<Airplane> airplane;          // Composition
   FlightDepartment flightDepartment;       // Composition
   AirplaneMaintenance airplaneMaintenance; // Composition

   // json objects to read files 
   json json_pilots;
   json json_medics;
   json json_flightAttendants;
   json json_inspectionManagers;
   json json_technicians;
   json json_customer;

   Airlines();
   ~Airlines() = default;
public:
   static Airlines *getInstance();

   // Customer Functionalities 
   bool addCustomer(Customer *customer);
   void updateCustomersFile();
   void customerEnd();
   void signUp();

   // Employee Functionalities
   void employeeEnd ();
   bool isUniqueEmployeeId (const std::string&);
   void displayEmployeeMenu(Employee*);

   // Admin functionalities
   void purchaseAirplanes();
   void displayAirplanes();
   bool addEmployee (Employee* employee);
   bool removeEmployee (const std::string& id);
   void updateEmployeesFile (const std::string&, const std::string&);
   void displayEmployees() const;
   void displayAllEmployees() const;

   template <class T>
   void displayByType (const std::string&)const;

   void markAttendance ();
   void transferSalary ();
   void displayCustomers () const;
   bool isAttendanceMarkedForToday();
   void flightDepartmentAdminEnd();

   void setCourier();
};

bool is_valid_tm(const std::tm& t);

#endif // _AIRLINES_H_
