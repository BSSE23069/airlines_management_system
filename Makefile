all: ./a.out

compRun:
	g++ -std=c++17 *.cpp Employees/*.cpp ErrorHandler/*.cpp Customers/*.cpp Company/*.cpp Accounts/*.cpp Users/*.cpp Salary/*.cpp Attendance/*.cpp Flight/*.cpp Departments/*.cpp Flight/Crew/*.cpp Airplane/Empennage/*.cpp Airplane/Engine/*.cpp Airplane/Fuselage/CargoCompartment/*.cpp Airplane/Fuselage/PassengerCompartment/PlaneSeat/*.cpp Airplane/Fuselage/PassengerCompartment/Window/*.cpp Airplane/Fuselage/PassengerCompartment/*.cpp Airplane/Fuselage/PassengerCompartment/OverHeadBin/*.cpp Airplane/Fuselage/*.cpp Airplane/Item/*.cpp Airplane/Landing_Gear/*.cpp Airplane/Wing/*.cpp Airplane/*.cpp cargoCompany/*.cpp -o r.out

compTest:
	g++ -std=c++17 *.cpp Employees/*.cpp ErrorHandler/*.cpp Customers/*.cpp Company/*.cpp Accounts/*.cpp Users/*.cpp Salary/*.cpp Attendance/*.cpp -o a.out

test: clean compTest; ./a.out

run: clean compRun; ./r.out

clean:
	rm -f *.out
