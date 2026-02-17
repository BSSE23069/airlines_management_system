#ifndef _MENU_H_
#define _MENU_H_
#include <unistd.h>

/*                          ***   Jamzee headers & cpp files   ***                     */

#include "Airplane/Airplane.h"
#include "Airplane//Engine/Engine.h"
#include "Airplane/Wing/Wing.h"
#include "Airplane/Empennage/Empennage.h"

#include "Airplane/Landing_Gear/LandingGear.h"
#include "Airplane/Landing_Gear/Tyre.h"
#include "Airplane/Landing_Gear/Strut.h"

#include "Airplane/Fuselage/Fuselage.h"
#include "Airplane/Fuselage/PassengerFuselage.h"
#include "Airplane/Fuselage/CargoFuselage.h"

#include "Airplane/Fuselage/CargoCompartment/CargoCompartment.h"

#include "Airplane/Fuselage/PassengerCompartment/PassengerCompartment.h"
#include "Airplane/Fuselage/PassengerCompartment/Window/Window.h"
#include "Airplane/Fuselage/PassengerCompartment/OverHeadBin/OverHeadBin.h"

#include "Airplane/Fuselage/PassengerCompartment/PlaneSeat/PlaneSeat.h"
#include "Airplane/Fuselage/PassengerCompartment/PlaneSeat/PremiumSeat.h"
#include "Airplane/Fuselage/PassengerCompartment/PlaneSeat/PreferredSeat.h"
#include "Airplane/Fuselage/PassengerCompartment/PlaneSeat/StandardSeat.h"
#include "Airplane/Fuselage/PassengerCompartment/PlaneSeat/LegRoomSeat.h"

#include "Airplane//Item/Item.h"
#include "Company/Company.h"
#include "Departments/AirplaneMaintenance.h"
#include "Airplane/Airplane.h"

/*                          ***   Jamzee headers & cpp files   ***                     */



// #include "Airplane/Engine/Engine.cpp"
// #include "Airplane/Wing/Wing.cpp"
// #include "Airplane/Empennage/Empennage.cpp"

// #include "Airplane/Landing_Gear/LandingGear.cpp"
// #include "Airplane/Landing_Gear/Tyre.cpp"
// #include "Airplane/Landing_Gear/Strut.cpp"

// #include "Airplane/Fuselage/Fuselage.cpp"
// #include "Airplane/Fuselage/PassengerFuselage.cpp"
// #include "Airplane/Fuselage/CargoFuselage.cpp"

// #include "Airplane/Fuselage/CargoCompartment/CargoCompartment.cpp"

// #include "Airplane/Fuselage/PassengerCompartment/PassengerCompartment.cpp"
// #include "Airplane/Fuselage/PassengerCompartment/Window/Window.cpp"
// #include "Airplane/Fuselage/PassengerCompartment/OverHeadBin/OverHeadBin.cpp"

// #include "Airplane/Fuselage/PassengerCompartment/PlaneSeat/PlaneSeat.cpp"
// #include "Airplane/Fuselage/PassengerCompartment/PlaneSeat/PremiumSeat.cpp"
// #include "Airplane/Fuselage/PassengerCompartment/PlaneSeat/PreferredSeat.cpp"
// #include "Airplane/Fuselage/PassengerCompartment/PlaneSeat/StandardSeat.cpp"
// #include "Airplane/Fuselage/PassengerCompartment/PlaneSeat/LegRoomSeat.cpp"

// #include "Airplane/Item/Item.cpp"
// #include "Company/Company.cpp"
// #include "Departments/AirplaneMaintenance.cpp"
// #include "Airplane/Airplane.cpp"


/*                          ***   Jamzee headers & cpp files   ***                     */

/*                                       HEADERS                                       */

#include "Accounts/Account.h"
#include "Accounts/AccountsManagement.h"
#include "Accounts/AirlinesAccount.h"

#include "Attendance/Attendance.h"

#include "Customers/Customer.h"

#include "Departments/Department.h"
#include "Departments/FlightDepartment.h"

#include "Employees/Employee.h"
#include "Employees/Admin.h"
#include "Employees/Technician.h"
#include "Employees/InspectionManager.h"
#include "Employees/FlightAttendant.h"
#include "Employees/Medic.h"
#include "Employees/pilot.h"

#include "Flight/Flight.h"
#include "Flight/Ticket.h"
#include "Flight/BookedTickets.h"

#include "Flight/Crew/Crew.h"

#include "Salary/Salary.h"

#include "Users/User.h"

#include "Airlines.h"
#include "ErrorHandler/ErrorHandler.h"

/*                                       HEADERS                                       */

/*                                       CPPS                                       */

// #include "Accounts/Account.cpp"
// #include "Accounts/AccountsManagement.cpp"
// #include "Accounts/AirlinesAccount.cpp"

// #include "Attendance/Attendance.cpp"

// #include "Customers/Customer.cpp"

// #include "Departments/Department.cpp"
// #include "Departments/FlightDepartment.cpp"

// #include "Employees/Employee.cpp"
// #include "Employees/Admin.cpp"
// #include "Employees/Technician.cpp"
// #include "Employees/InspectionManger.cpp"
// #include "Employees/FlightAttendant.cpp"
// #include "Employees/Medic.cpp"
// #include "Employees/pilot.cpp"

// #include "Flight/Flight.cpp"
// #include "Flight/Ticket.cpp"
// #include "Flight/BookedTickets.cpp"

// #include "Flight/Crew/Crew.cpp"

// #include "Salary/Salary.cpp"

// #include "Users/User.cpp"

// #include "Airlines.cpp"
// #include "ErrorHandler/ErrorHandler.cpp"



// /*                                         CPPS                                       */

// /*                                         CARGO                                      */

// #include "cargoCompany/Courier.cpp"
// #include "cargoCompany/Delivery.cpp"
// #include "cargoCompany/Person.cpp"
// #include "cargoCompany/Sender.cpp"
// #include "cargoCompany/Receiver.cpp"
// #include "cargoCompany/Address.cpp"
// #include "cargoCompany/Items.cpp"

#include "cargoCompany/Courier.h"
#include "cargoCompany/Delivery.h"
#include "cargoCompany/Person.h"
#include "cargoCompany/Sender.h"
#include "cargoCompany/Receiver.h"
#include "cargoCompany/Address.h"
#include "cargoCompany/Items.h"

/*                                         CARGO                                      */

void Menu();

#endif // Menu
