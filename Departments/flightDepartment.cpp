#include "FlightDepartment.h"

FlightDepartment::FlightDepartment(std::vector<Airplane> &airplane, std::vector<Customer *> &customers) : airplanes(
                                                                                                            airplane),
                                                                                                          customers(customers)
{
}

int FlightDepartment::checkFlightNumber()
{
    std::string flightnumber;
    std::cout << "Enter the flight number you want to choose.\n";
    std::cin >> flightnumber;

    for (int i = 0; i < flights.size(); i++) // Check all the flights to match this flight number
    {
        if (flights[i].getFlightNumber() == flightnumber)
        { // Check if flight number matches
            std::cout << "Flight Number Found/Available!" << endl;
            return i; // Return the index on which flightNumber was found
        }
    }
    return -1;
}

void FlightDepartment::addPassengers(int customerIndex)
{
    int x;

    do
    {
        std::cout << "Enter :-\n[1] to buy the seat right now.\n[2] to book a seat and pay later.\n[3] to pay the price of booked seats.\n[4] too display your tickets history.\n[5] to exit.\n";
        std::cin >> x;
        switch (x)
        {
        case 1:
        {
            int y;

            std::string departure, Arrival;
            int z = 1;
            bool isAv;
            std::cout << "Enter the Departure place of the flight : ";
            std::cin >> departure;
            std::cout << "Enter the Destination of the flight : ";
            std::cin >> Arrival;
            isAv = checkArrivalAndDeparture(departure, Arrival);

            if (!isAv)
                break;
            int i;
            displayFlights(departure, Arrival);
            do
            {
                i = checkFlightNumber();
            } while (i == -1);
            do
            {
                // displaying the flights
                Ticket ticket = flights[i].buySeat(customers[customerIndex]->getId());

                if (ticket.getSeatNumber() != "NAN")
                {

                    customers[customerIndex]->addTicket(ticket);
                    /* code */
                }
                incrementAndDecrementOfAvailableSeats(i);
                std::cout << "Enter -ve integer to stop the process and +ve to continue.\n";
                std::cin >> y;

            } while (y > 0);

            break;
        }
        case 2:
        {

            std::string departure, Arrival;
            int z = 1;
            bool isAv;

            int y;
            std::cout << "Enter the Departure place of the flight : ";
            std::cin >> departure;
            std::cout << "Enter the Destination of the flight : ";
            std::cin >> Arrival;
            isAv = checkArrivalAndDeparture(departure, Arrival);

            if (!isAv)
                break;
            int i;
            displayFlights(departure, Arrival);
            do
            {
                i = checkFlightNumber();
            } while (i == -1);
            do
            {
                // displaying the flights
                BookedTickets ticket = flights[i].bookSeat(customers[customerIndex]->getId());

                if (ticket.getSeatNumber() != "NAN")
                {
                    customers[customerIndex]->addBookedTicket(ticket);
                    /* code */
                }
                incrementAndDecrementOfAvailableSeats(i);
                std::cout << "Enter -ve integer to stop the process and +ve to continue.\n";
                std::cin >> y;
                // flights[i].displayBookedAndNormalSeats();

            } while (y > 0);

            break;
        }
        case 3:
        {
            payPriceOfBookedTicket(customerIndex);
            break;
        }
        case 4:
        {
            customers[customerIndex]->displayTicketsHistory();
            break;
        }
        case 5:
        {
            std::cout << "Bye.\n";
            break;
        }

        default:
        {
            std::cout << "Invalid Input.\n";
            break;
        }
        }
    } while (x != 5);
}

bool FlightDepartment::checkIfFightNumberAvailable(std::string number)
{
    int j = 0;
    for (int i = 0; i < flights.size(); ++i)
    {
        if (flights[i].getFlightNumber() == number)
        {
            j++;
        }
    }
    if (j == 0)
    {
        return true;
    }
    return false;
}

void FlightDepartment::addFlight()
{
    bool isFlightNumAv;
    std::string flight, departure, Arrival;
    std::cout << "Enter the Departure place of the flight : ";
    std::cin >> departure;
    std::cout << "Enter the Destination of the flight : ";
    std::cin >> Arrival;
    do
    {
        std::cout << "Assign the Flight Number to the Flight : ";
        std::cin >> flight;
        isFlightNumAv = checkIfFightNumberAvailable(flight);
        if (!isFlightNumAv)
        {
            std::cout << "Number already occupied.";
        }
    } while (!isFlightNumAv);
    Flight flight1(departure, Arrival, flight);
    // displaying planes
    bool validID;
    std::string ID;
    do
    {
        displayAvailablePlanes();
        std::cout << "Enter the ID of Plane you want to assign to this flight.\n";
        std::cin.ignore();
        std::cin >> ID;
        validID = checkPlaneID(ID);
    } while (!validID);

    for (int i = 0; i < airplanes.size(); ++i)
    {
        if (ID == airplanes[i].getPlaneID())
        {
            airplanes[i].setFlightStatus(true);

            flight1.setAirplane(airplanes[i]);
        }
    }
    flight1.setArrival();
    flight1.setAvailableSeats();
    flights.push_back(flight1);
    int i = flights.size();

    sendObjectToWriteFlights(flight1); // Send the latest pushed back object to this function for filing
}

bool FlightDepartment::checkPlaneID(std::string &ID)
{
    int j = 0;
    for (int i = 0; i < airplanes.size(); i++)
    {
        if (ID == airplanes[i].getPlaneID())
        {
            return true;
        }
    }
    return false;
}

void FlightDepartment::sendObjectToWriteFlights(Flight flights)
{
    json object = {

        {"departure", flights.getDeparture()},
        {"availableSeats", flights.getAvailableSeats()},
        {"destination", flights.getDestination()},
        {"departureTime", flights.getDepartureTime()},
        {"arrivalTime", flights.getArrivalTime()},
        {"flightNumber", flights.getFlightNumber()},
        {"planeID", flights.getPlaneID()},
    };

    jsonFlights.push_back(object);
    //    ofstream out("C:\\Users\\Scorp Radoz\\Documents\\GitHub\\2024-Spring-SE102TB-Project-se102b-e\\Departments\\flights.json" ,ios::trunc);
    ofstream out("C:\\OOPS_PROJECT_EXTENDED\\2024-Spring-SE102TB-Project-se102b-e\\Departments\\flights.json", ios::trunc);
    out << jsonFlights;
    out.close();
}

void FlightDepartment::saveFlightToFile()
{

    for (int i = 0; i < flights.size(); i++)
    {
        // sendObjectToWriteFlights(i); //Call for each index
    }
}

void FlightDepartment::readFlights()
{
    //    ifstream input("C:\\Users\\Scorp Radoz\\Documents\\GitHub\\2024-Spring-SE102TB-Project-se102b-e\\Departments\\flights.json");
    ifstream input("C:\\OOPS_PROJECT_EXTENDED\\2024-Spring-SE102TB-Project-se102b-e\\Departments\\flights.json");
    if (!input.is_open())
    {
        std::cout << "\n";
    }
    if (input.peek() == ifstream::traits_type::eof())
    {
        std::cout << "\n";
    }
    else
    {
        input >> jsonFlights;
    }
    input.close();

    //    json crewJson;
    //    int totalNoOfCrews = 0;
    //    loadCrews(crewJson, totalNoOfCrews);
    for (int i = 0; i < jsonFlights.size(); i++)
    {
        std::string str = "NAN";
        Flight flight(str, str, str);
        flight.readFlight(jsonFlights[i]);

        //        for (int j = 0; j < crews.size(); i++) {
        //            if (crews[j].getFlightNumber() == flights[i].getFlightNumber()) {
        //                flights[i].setCrew(crews[j]); //Start pointing at that crew
        //            }
        //
        //        }
        for (int j = 0; j < airplanes.size(); j++)
        {
            if (airplanes[j].getPlaneID() == flight.getPlaneID())
            {

                flight.setAirplane(airplanes[j]);
            }
        }
        double hours;
        hours = (flight.getArrivalTime() - flight.getDepartureTime()) / 3600;
        flight.setSeatPrice(hours);
        flights.push_back(flight);
    }
}

bool FlightDepartment::checkArrivalAndDeparture(std::string departure, std::string arrival)
{
    int j = 0;
    for (int i = 0; i < flights.size(); ++i)
    {
        if (flights[i].getDeparture() == departure && arrival == flights[i].getDestination())
        {
            j++;
        }
    }
    if (j == 0)
    {
        return false;
    }
    return true;
}

void FlightDepartment::displayFlights()
{
    for (int i = 0; i < flights.size(); ++i)
    {
        flights[i].displayFlight();
    }
}

void FlightDepartment::assignCrewToFlights()
{

    json crewJson; // Load previous data
    ifstream in("crews.json");
    if (in.is_open())
    {

        in >> crewJson;
        in.close();
    }

    int x = 1;
    string flightNum;
    do
    {
        for (int i = 0; i < flights.size(); ++i)
        {
            flights[i].displayFlight();
            std::cout << "=======================================\n";
        }
        std::cout << "Enter the Flight Number you want to assign crew to.\n";
        cin.ignore();
        std::cin >> flightNum;
        for (int i = 0; i < flights.size(); i++)
        {
            if (flightNum == flights[i].getFlightNumber())
            {

                for (int j = 0; j < crews.size(); j++)
                {
                    if (crews[j].getFlightNumber() == "NAN")
                        std::cout << "Crew Number : " << j + 1 << std::endl;
                    std::cout << crews[j];
                }
                std::cout << "Enter the Crew Number You want to assign to the flight : ";
                int l;
                std::cin >> l;
                crews[l - 1].setFlightNumber(flights[i].getFlightNumber());
            }
        }
        std::cout << "Enter -ve integer to stop the process and +ve to continue.\n";
        std::cin >> x;
    } while (x > 0);
}

void FlightDepartment::displayFlights(std::string departure, std::string arrival)
{
    for (int i = 0; i < flights.size(); ++i)
    {
        if (flights[i].getDeparture() == departure && arrival == flights[i].getDestination() && flights[i].getAvailableSeats() != 0)
        {
            flights[i].displayFlight();
        }
    }
}

void FlightDepartment::payPriceOfBookedTicket(int i)
{
    int x = 1;
    do
    {
        BookedTickets tickets = customers[i]->payPriceOfTickets();
        if (tickets.getDeparture() != "NAN")
        {
            for (int j = 0; j < flights.size(); ++j)
            {
                if (tickets.getFlightNumber() == flights[j].getFlightNumber())
                {
                    if (flights[j].checkBookedTicket(tickets))
                    {
                        // cuts the price
                        Account account;
                        std::cout << "Enter the Account Number you want to pay the money through : ";
                        std::string accountNo;
                        std::cin.ignore();
                        std::cin >> accountNo;
                        account.removeBalanceDirectly(accountNo, tickets.getPrice());
                        customers[i]->addTicketAfterPayingPrice(tickets);
                        std::cout << "Price paid Successfully.\n";
                    }
                }
            }
        }
        else
        {
            cout << "You don't have any pay able tickets.\n";
        }
        std::cout << "Enter -ve integer to stop the process and +ve to continue.\n";
        std::cin >> x;
    } while (x > 0);
}

void FlightDepartment ::displayCrews(json &crewsJson, int &totalNoOfCrews)
{

    cout << "Total number of crews: " << totalNoOfCrews << endl; // Display the total no of Crews

    cout << "Already Existing Crews: -" << endl; // Display already existing crews, display empty if no crews exist already

    // for (int i = 0; i < crews.size(); i++)
    // {
    //     cout << "Crew Number: " << crews[i].getCrewNumber() << endl;
    // }

    for (int i = 0; i < crews.size(); i++)
    {
        cout << "Crew #" << crews[i].getCrewNumber() << endl;
        cout << "Pilot ID: " << crews[i].getPilot() << endl;
        cout << "Co-Pilot ID: " << crews[i].getCoPilot() << endl;
        cout << "Purser ID: " << crews[i].getPurser() << endl;
        cout << endl;
        cout << "Flight Attendants: -" << endl;

        for (int j = 0; j < crews[i].getFlightAttendant().size(); j++) // Display this crew's flight attendanta
        {

            cout << "Flight Attendant# " << j + 1 << "'s ID: " << crews[i].getFlightAttendant()[j] << endl;
        }
        cout << endl;

        cout << "Medics: -" << endl;

        for (int k = 0; k < crews[i].getMedic().size(); k++) // Display this crew's medics
        {
            cout << "Medic #" << k + 1 << "'s ID: " << crews[i].getMedic()[k] << endl;
        }

        cout << endl;
    }
}

void FlightDepartment::loadCrews(json &crewsJson, int &totalNoOfCrews)
{
    //    string filepath = "c:\\Users\\HP\\Desktop\\Programming\\Project\\Testing\\2024-Spring-SE102TB-Project-se102b-e\\Departments\\crews.json";
    string filepath = "C:\\OOPS_PROJECT_EXTENDED\\2024-Spring-SE102TB-Project-se102b-e\\Departments\\crews.json";
    ifstream inCrew(filepath); // Load the already existing JSON file for crews
    if (inCrew.is_open())
    {
        inCrew >> crewsJson;
        inCrew.close();
        cout << "File is opened!" << endl;
        totalNoOfCrews = crewsJson["totalNoOfCrews"];
        for (int i = 0; i < crewsJson["crews"].size(); i++)
        {
            Crew tempCrew;
            // Load the totalNoOfCrews
            tempCrew.setCoPilot(crewsJson["crews"][i]["coPilotID"]); // Load Pilots
            tempCrew.setPilot(crewsJson["crews"][i]["pilotID"]);     // Load Co Pilots

            tempCrew.setPurser(crewsJson["crews"][i]["purserID"]);
            tempCrew.setCrewNumber(crewsJson["crews"][i]["crewNumber"]); // Load Crew Numbers
            // cout << "Crew Number: " << tempCrew.getCrewNumber() << endl;

            for (int j = 0; j < crewsJson["crews"][i]["medics"].size(); j++) // Load medics
            {
                tempCrew.setMedic(crewsJson["crews"][i]["medics"][j]["medicID"]);
            }
            for (int j = 0; j < crewsJson["crews"][i]["flightAttendants"].size(); j++) // Load Flight Attendants
            {
                tempCrew.setFlightAttendant(crewsJson["crews"][i]["flightAttendants"][j]["flightAttendantID"]);
            }

            crews.push_back(tempCrew); // Push Back The Newly Made Object
        }
    }
}

void FlightDepartment ::makeNewCrew()
{
    loadCrewEmployees();
    json crewsJson;
    int totalNoOfCrews = 0;
    loadCrews(crewsJson, totalNoOfCrews); // Load existing crews
                                          //    string filepath = "c:\\Users\\HP\\Desktop\\Programming\\Project\\Testing\\2024-Spring-SE102TB-Project-se102b-e\\Departments\\crews.json";
    string filepath = "C:\\OOPS_PROJECT_EXTENDED\\2024-Spring-SE102TB-Project-se102b-e\\Departments\\crews.json";
    json other;
    int incrementCrewNumber = 0;

    ifstream in2(filepath); // Load the file again to load incrementCrewNumber
    if (in2.is_open())
    {
        in2 >> crewsJson;
        incrementCrewNumber = crewsJson["incrementCrewNumber"];
        in2.close();
    }

    cout << "Welcome to Crew Addition Function!" << endl;
    displayCrews(crewsJson, totalNoOfCrews); // Display the already existing crews

    cout << "How many new crews do you want to add?: "; // How many new crews?

    int numCrews = 0;
    cin >> numCrews;

    bool verify = true;
    if (pilots.size() < (numCrews * 2))
    {
        cout << "Not Enough Pilots/Co Pilots!" << endl;
        cout << (numCrews * 2) - pilots.size() << " More Pilots/Co Pilots Required!" << endl;
        verify = false;
    }
    if (medics.size() < (numCrews * 2))
    {
        cout << "Not Enough Medics/Pursers!" << endl;
        cout << (numCrews * 2) - medics.size() << " More Medics/Pursers Required!" << endl;
        verify = false;
    }
    if (flightAttendants.size() < (numCrews))
    {
        cout << "Not Enough Flight Attendants!" << endl;
        cout << (numCrews)-flightAttendants.size() << " More Flight Attendants Required!" << endl;
        verify = false;
    }

    if (!verify)
    {
        return;
    }

    cout << endl;
    int crewNumber = 1;

    for (int i = totalNoOfCrews; i < (totalNoOfCrews + numCrews); i++) // Run the loop from already existing index to numCrews
    {
        cout << "Crew# " << crewNumber << endl; // Display crew Number while ling
        crewNumber++;
        Crew tempCrew;
        crews.push_back(tempCrew); // Create an index
        setCrew(crewsJson, i);     // Call this member function of Crews
        incrementCrewNumber++;
        crews[i].setCrewNumber(incrementCrewNumber);
        // int incrementCrewNumber = Crew::getCrewNumber();

        // Crew::setCrewNumber(incrementCrewNumber);
        crewsJson["crews"][i]["crewNumber"] = incrementCrewNumber;
        crewsJson["incrementCrewNumber"] = incrementCrewNumber;
    }

    totalNoOfCrews += numCrews; // Update the totalNoOfCrews

    crewsJson["totalNoOfCrews"] = totalNoOfCrews; // Save the totalNoOfCrews
    ofstream outCrew(filepath);                   // Make the file
    outCrew << crewsJson;
    outCrew.close();

    saveCrewEmployees();
    cout << "Crew has been added!" << endl;
}

bool FlightDepartment::verifyEditedID(string newID, string previousID)
{
    for (int i = 0; i < pilots.size(); i++)
    {
        if (newID == pilots[i]->getId())
        {
            usedPilots.push_back(pilots[i]);
            pilots.erase(pilots.begin() + i); // Remove from original vector
            for (int j = 0; j < usedPilots.size(); j++)
            {
                if (previousID == usedPilots[j]->getId())
                {
                    pilots.push_back(usedPilots[j]); // Return to original vector if needed
                    usedPilots.erase(usedPilots.begin() + j);
                    return true; // Return true after successful transfer and removal
                }
            }
            return true; // Return true after successful transfer and removal
        }
    }

    for (int i = 0; i < medics.size(); i++)
    {
        if (newID == medics[i]->getId())
        {
            usedMedic.push_back(medics[i]);
            medics.erase(medics.begin() + i); // Remove from original vector
            for (int j = 0; j < usedMedic.size(); j++)
            {
                if (previousID == usedMedic[j]->getId())
                {
                    cout << "Previos ID For Medics Found!" << endl;
                    medics.push_back(usedMedic[j]); // Return to original vector if needed
                    usedMedic.erase(usedMedic.begin() + j);
                    return true; // Return true after successful transfer and removal
                }
            }
            cout << "Current ID Of Medic Not Matching!" << endl;
            return false;
        }
    }

    for (int i = 0; i < flightAttendants.size(); i++)
    {
        if (newID == flightAttendants[i]->getId())
        {
            usedFlightAttendants.push_back(flightAttendants[i]);
            flightAttendants.erase(flightAttendants.begin() + i); // Remove from original vector
            for (int j = 0; j < usedFlightAttendants.size(); j++)
            {
                if (previousID == usedFlightAttendants[j]->getId())
                {
                    flightAttendants.push_back(usedFlightAttendants[j]); // Return to original vector if needed
                    usedFlightAttendants.erase(usedFlightAttendants.begin() + j);
                    return true; // Return true after successful transfer and removal
                }
            }
            cout << "Current ID Of Flight Attendant Not Matching!" << endl;
            return false;
        }
    }

    cout << "The provided id does not match with any id" << endl;
    return false;
}

void FlightDepartment::editCrew()
{
    // viewVectors();
    // saveCrewEmployees();
    // loadCrewEmployees();
    //    string filepath = "c:\\Users\\HP\\Desktop\\Programming\\Project\\Testing\\2024-Spring-SE102TB-Project-se102b-e\\Departments\\crews.json";
    string filepath = "C:\\OOPS_PROJECT_EXTENDED\\2024-Spring-SE102TB-Project-se102b-e\\Departments\\crews.json";
    json crewsJson;
    int totalNoOfCrews = 0;
    loadCrews(crewsJson, totalNoOfCrews); // Load existing crews

    displayCrews(crewsJson, totalNoOfCrews); // Display the existing Crews

    int editCrewNumber; // The crew number which user wants to edit
    do
    {
        cout << "Please enter the crew number which you want to edit, [0]Finish Editing Crews: ";
        cin >> editCrewNumber;
        cout << endl;

        if (editCrewNumber == 0)
        {
            saveCrewEmployees();
            return;
        }

        bool found = false;
        for (int i = 0; i < crews.size(); i++)
        {
            if (editCrewNumber == crewsJson["crews"][i]["crewNumber"])
            {
                found = true;
                cout << "[1]Change Pilot, [2]Change Co-Pilot, [3]Change Medic, [4]Change Flight Attendants, [5]Change Purser [6]Exit: ";
                int x;
                cin >> x;
                switch (x)
                {
                case 1:
                {
                    cout << "Current Pilot ID: " << crewsJson["crews"][i]["pilotID"] << endl;
                    cout << "Available Pilot IDs: ";
                    for (const auto &pilot : pilots)
                    {
                        cout << pilot->getId() << " ";
                    }
                    cout << endl;
                    cout << "[1]Input new ID, [2]Return: ";
                    int y;
                    cin >> y;
                    if (y == 1)
                    {
                        string newID;
                        cout << "ID: ";
                        cin >> newID;
                        if (verifyEditedID(newID, crewsJson["crews"][i]["pilotID"]))
                        {
                            crews[i].setPilot(newID);
                            crewsJson["crews"][i]["pilotID"] = newID;
                            cout << "The ID has been replaced!" << endl;
                            ofstream outCrew(filepath);
                            outCrew << crewsJson;
                            outCrew.close();
                        }
                    }
                    break;
                }
                case 2:
                {
                    cout << "Current Co Pilot ID: " << crewsJson["crews"][i]["coPilotID"] << endl;
                    cout << "Available Co Pilots IDs: ";
                    for (const auto &coPilot : pilots)
                    {
                        cout << coPilot->getId() << " ";
                    }
                    cout << endl;
                    cout << "[1]Input new ID, [2]Return: ";
                    int y;
                    cin >> y;
                    if (y == 1)
                    {
                        string newID;
                        cout << "ID: ";
                        cin >> newID;
                        if (verifyEditedID(newID, crewsJson["crews"][i]["coPilotID"]))
                        {
                            crews[i].setCoPilot(newID);
                            crewsJson["crews"][i]["coPilotID"] = newID;
                            cout << "The ID has been replaced!" << endl;
                            ofstream outCrew(filepath);
                            outCrew << crewsJson;
                            outCrew.close();
                        }
                    }
                    break;
                }
                case 3:
                {
                    cout << "Current Medics: ";
                    for (const auto &medic : crews[i].getMedic())
                    {
                        cout << medic << " ";
                    }
                    cout << endl;
                    cout << "Available Medics: ";
                    for (const auto &medic : medics)
                    {
                        cout << medic->getId() << " ";
                    }
                    cout << endl;
                    cout << "[1]Change a Medic, [2]Remove A Medic, [3]Exit: ";
                    int choice;
                    cin >> choice;
                    if (choice == 1)
                    {
                        cout << "Which Medic To Change(ID): ";
                        string previousID;
                        cin >> previousID;
                        cout << endl;
                        cout << "Enter new medic's ID: ";
                        string newID;
                        cin >> newID;

                        if (verifyEditedID(newID, previousID) == true)
                        {
                            int medicIndex = crewsJson["crews"][i]["medicsIndex"];
                            for (int o = 0; o < medicIndex; o++)
                            {
                                if (previousID == crewsJson["crews"][i]["medics"][o]["medicID"])
                                {
                                    crewsJson["crews"][i]["medics"][o]["medicID"] = newID;

                                    ofstream outCrew(filepath);
                                    outCrew << crewsJson;
                                    outCrew.close();
                                    cout << "Medic has been replaced!" << endl;
                                    saveCrewEmployees();
                                    editCrew();
                                }
                                else
                                {
                                    cout << "Previous ID of Medic not found inside json file" << endl;
                                    return;
                                }
                            }
                        }
                        else
                        {
                            cout << "ID not matching!" << endl;
                            return;
                        }
                    }

                    if (choice == 2)
                    {
                        cout << "Which Medic To Remove: (ID): ";
                        string removeID;
                        cin >> removeID;

                        for (int m = 0; m < crews[i].getMedic().size(); m++)
                        {
                            if (removeID == crews[i].getMedic()[m])
                            {

                                crews[i].getMedic().erase(crews[i].getMedic().begin() + m); // Remove the medic from crew's medic vector
                                crewsJson["crews"][i]["medics"].erase(crewsJson["crews"][i]["medics"].begin() + m);
                                removeCrewMember(removeID);

                                ofstream outCrew(filepath);
                                outCrew << crewsJson;
                                outCrew.close();
                                saveCrewEmployees();
                                editCrew();
                            }
                        }
                    }
                    break;
                    if (choice == 3)
                    {
                        cout << "Exiting.." << endl;
                        return;
                    }
                    break;
                }
                case 4:
                {
                    cout << "Current Flight Attendants: ";
                    for (const auto &attendant : crews[i].getFlightAttendant())
                    {
                        cout << attendant << " ";
                    }
                    cout << endl;
                    cout << "Available Flight Attendants: ";
                    for (const auto &attendant : flightAttendants)
                    {
                        cout << attendant->getId() << " ";
                    }
                    cout << endl;
                    cout << "[1]Change a Flight Attendant, [2]Remove A Flight Attendant, [3]Exit: ";
                    int choice;
                    cin >> choice;
                    if (choice == 1)
                    {
                        cout << "Which Flight Attendant To Change(ID): ";
                        string previousID;
                        cin >> previousID;
                        cout << endl;
                        cout << "Enter new Flight Attendant's ID: ";
                        string newID;
                        cin >> newID;

                        if (verifyEditedID(newID, previousID) == true)
                        {
                            for (int p = 0; p < crews[i].getFlightAttendant().size(); i++)
                            {
                                if (previousID == crews[i].getFlightAttendant()[p])
                                {
                                    crewsJson["crews"][i]["flightAttendants"][p]["flightAttendantID"] = newID;

                                    ofstream outCrew(filepath);
                                    outCrew << crewsJson;
                                    outCrew.close();
                                    saveCrewEmployees();
                                    cout << "Flight Attendant has been replaced!" << endl;
                                    editCrew();
                                }
                            }
                        }
                        else
                        {
                            cout << "ID not matching!" << endl;
                            return;
                        }
                    }

                    if (choice == 2)
                    {
                        cout << "Which Flight Attendant To Remove: (ID): ";
                        string removeID;
                        cin >> removeID;

                        for (int m = 0; m < crews[i].getFlightAttendant().size(); m++)
                        {
                            if (removeID == crews[i].getFlightAttendant()[m])
                            {

                                crews[i].getFlightAttendant().erase(crews[i].getFlightAttendant().begin() + m); // Remove the medic from crew's medic vector
                                crewsJson["crews"][i]["flightAttendants"].erase(crewsJson["crews"][i]["flightAttendants"].begin() + m);
                                removeCrewMember(removeID);

                                ofstream outCrew(filepath);
                                outCrew << crewsJson;
                                outCrew.close();
                                saveCrewEmployees();
                                editCrew();
                            }
                            else
                            {
                                cout << "The given ID doesn't match!" << endl;
                            }
                        }
                    }
                    break;
                    if (choice == 3)
                    {
                        cout << "Exiting.." << endl;
                        return;
                    }
                    break;
                }
                case 6:
                {
                    cout << "Exiting Crews Menu!" << endl;
                    saveCrewEmployees();
                    return;
                }
                case 5:
                {
                    cout << "Current Purser ID: " << crewsJson["crews"][i]["purserID"] << endl;
                    cout << "Available Purser IDs: ";
                    for (const auto &medic : medics)
                    {
                        cout << medic->getId() << " ";
                    }
                    cout << endl;
                    cout << "[1]Input new ID, [2]Return: ";
                    int y;
                    cin >> y;
                    if (y == 1)
                    {
                        string newID;
                        cout << "ID: ";
                        cin >> newID;
                        if (verifyEditedID(newID, crewsJson["crews"][i]["purserID"]))
                        {
                            crews[i].setPilot(newID);
                            crewsJson["crews"][i]["purserID"] = newID;
                            cout << "The ID has been replaced!" << endl;
                            ofstream outCrew(filepath);
                            outCrew << crewsJson;
                            outCrew.close();
                        }
                    }
                    break;
                }
                default:
                    cout << "Invalid choice!" << endl;
                }
                break;
            }
        }
        if (!found)
        {
            cout << "Sorry, the Crew Number doesn't exist!" << endl;
        }
    } while (editCrewNumber != 0);
}

void FlightDepartment::removeCrewMember(string removeID)
{
    for (int i = 0; i < usedMedic.size(); i++)
    {
        if (removeID == usedMedic[i]->getId())
        {
            medics.push_back(usedMedic[i]);
            usedMedic.erase(usedMedic.begin() + i);
            cout << "Given ID is from Used Medics, It has been removed!" << endl;
            return;
        }
    }

    for (int i = 0; i < usedFlightAttendants.size(); i++)
    {
        if (removeID == usedFlightAttendants[i]->getId())
        {
            flightAttendants.push_back(usedFlightAttendants[i]);
            usedFlightAttendants.erase(usedFlightAttendants.begin() + i);
            cout << "Given ID is from Used Used Flight Attendants, It has been removed!" << endl;
            return;
        }
    }

    cout << "Not Matching IDs" << endl;
}

void FlightDepartment ::setCrew(json &crewsJson, int &index)
{ // Called by Flight Department's makeNewCrew

    cout << "Available Pilots: -" << endl; // Display Pilots
    // cout << "Pilots size: " << pilots.size();
    for (int i = 0; i < pilots.size(); i++)
    {
        cout << pilots[i]->getId() << endl;
    }

    addPilot(crewsJson, index);

    cout << "Available Co-Pilots: -" << endl; // Display Co Pilots
    for (int i = 0; i < pilots.size(); i++)
    {
        cout << pilots[i]->getId() << endl;
    }

    addCoPilot(crewsJson, index);

    cout << endl;
    cout << "Avalilable Medics: -" << endl;

    for (int i = 0; i < medics.size(); i++) // Display Medics
    {
        cout << medics[i]->getId() << endl;
    }
    cout << endl;

    addMedics(crewsJson, index);

    cout << "Avalilable Pursers: -" << endl;

    for (int i = 0; i < medics.size(); i++) // Display Pursers
    {
        cout << medics[i]->getId() << endl;
    }
    cout << endl;
    addPurser(crewsJson, index);

    cout << "Available Flight Attendants: -" << endl;

    for (int i = 0; i < flightAttendants.size(); i++) // Display Flight Attendants
    {
        cout << flightAttendants[i]->getId() << endl;
    }

    addFlightAttendants(crewsJson, index);
}

bool FlightDepartment ::verifyCrewMember(string ID)
{ // Verify if the ID exists in any 3 of the vectors present inside FlightDepartment

    for (int i = 0; i < pilots.size(); i++)
    {
        if (ID == pilots[i]->getId())
        {
            usedPilots.push_back(pilots[i]); // Transfer the pilot to used pilots
            // cout << "Pused into used pilots!" << endl;
            pilots.erase(pilots.begin() + i);
            // cout << "Removed from idle pilots!" << endl;
            // cout << "Returning true!" << endl;
            return true;
        }
    }

    for (int j = 0; j < medics.size(); j++)
    {
        if (ID == medics[j]->getId())
        {
            usedMedic.push_back(medics[j]); // Transfer the medic to used medic
            medics.erase(medics.begin() + j);

            return true;
        }
    }

    for (int k = 0; k < flightAttendants.size(); k++)
    {
        if (ID == flightAttendants[k]->getId())
        {
            usedFlightAttendants.push_back(flightAttendants[k]); // Transfer the flightAttendant to used flight Attendants
            flightAttendants.erase(flightAttendants.begin() + k);
            return true;
        }
    }

    return false; // If all the loops run and nothing is found, return false
}

void FlightDepartment ::addPurser(json &crewsJson, int &crewIndex)
{
    std::string newPurserID;
    cout << "Which Purser do you want to add: ";
    cin >> newPurserID;
    cout << endl;
    if (verifyCrewMember(newPurserID) == true)
    {
        crews[crewIndex].setPurser(newPurserID);
        crewsJson["crews"][crewIndex]["purserID"] = newPurserID;
        cout << "Purser has been added!" << endl;
    }
    else
    {
        cout << "Sorry, the ID doesn't match!" << endl;
        addPurser(crewsJson, crewIndex);
    }
}

void FlightDepartment ::addPilot(json &crewsJson, int &crewIndex)
{
    std::string newPilotID;
    cout << "Which Pilot do you want to add: ";
    cin >> newPilotID;
    cout << endl;
    if (verifyCrewMember(newPilotID) == true)
    {
        cout << "Returned pilot verify true!" << endl;
        crews[crewIndex].setPilot(newPilotID);
        cout << "Pilot id set in crew!" << endl;
        crewsJson["crews"][crewIndex]["pilotID"] = newPilotID;
        cout << "Pilot has been added!" << endl;
    }
    else
    {
        cout << "Sorry, the ID doesn't match!" << endl;
        addPilot(crewsJson, crewIndex);
    }
}

void FlightDepartment ::addCoPilot(json &crewsJson, int &crewIndex)
{
    std::string newCoPilotID;
    cout << "Which coPilot do you want to add: ";
    cin >> newCoPilotID;
    cout << endl;
    if (verifyCrewMember(newCoPilotID) == true)
    {
        crews[crewIndex].setCoPilot(newCoPilotID);
        crewsJson["crews"][crewIndex]["coPilotID"] = newCoPilotID;
        cout << "Pilot has been added!" << endl;
    }
    else
    {
        cout << "Sorry, the ID doesn't match!" << endl;
        addCoPilot(crewsJson, crewIndex);
    }
}

void FlightDepartment ::addFlightAttendants(json &crewsJson, int &crewIndex)
{
    std::string newFlightAttendantID;
    // int flightAttendantIndex = crewsJson["crews"][crewIndex]["flightAttendantsIndex"];
    int flightAttendantIndex = 0;

    do
    {
        cout << "Wich Flight Attendant do you want to add, [0]Finish Adding: ";
        cin >> newFlightAttendantID;
        cout << endl;

        if (newFlightAttendantID == "0")
        {
            return;
        }

        if (verifyCrewMember(newFlightAttendantID) == true)
        {
            crews[crewIndex].setFlightAttendant(newFlightAttendantID);
            crewsJson["crews"][crewIndex]["flightAttendants"][flightAttendantIndex]["flightAttendantID"] = newFlightAttendantID;
            flightAttendantIndex++;
            crewsJson["crews"][crewIndex]["flightAttendantsIndex"] = flightAttendantIndex;
            cout << "Flight Attendant has been added!" << endl;
        }
        else
        {
            cout << "Sorry, the ID doesn't match" << endl;
            addFlightAttendants(crewsJson, crewIndex);
        }
    } while (newFlightAttendantID != "0");
}

void FlightDepartment ::addMedics(json &crewsJson, int &crewIndex)
{

    std::string newMedicID;
    int medicsIndex = 0;

    // medicsIndex = crewsJson["crews"][crewIndex]["medicsIndex"];

    do
    {
        cout << "Which Medic do you want to add, [0]Finish Adding: ";
        cin >> newMedicID;
        cout << endl;

        if (newMedicID == "0")
        {
            return;
        }

        if (verifyCrewMember(newMedicID) == true)
        {
            crews[crewIndex].setMedic(newMedicID);
            crewsJson["crews"][crewIndex]["medics"][medicsIndex]["medicID"] = newMedicID;
            medicsIndex++;
            crewsJson["crews"][crewIndex]["medicsIndex"] = medicsIndex;
            cout << "Medic has been added!" << endl;
        }
        else
        {
            cout << "Sorry, the ID doesn't match" << endl;
            addFlightAttendants(crewsJson, crewIndex);
        }
    } while (newMedicID != "0");
}

void FlightDepartment ::removeFlight(AirplaneMaintenance &maintainance)
{
    json crewJson;
    int totalNoOfCrews = 0;
    int k = 0;
    loadCrews(crewJson, totalNoOfCrews);
    displayFlights();
    std::cout << std::endl;
    cout << "Please enter the flight number you want to remove: ";
    string removeFlightNumber;
    cin >> removeFlightNumber;
    std::cout << "Enter : -\n [1] if you are cancelling the flight.\n[0] if you are removing the flight aftr it has landed.\n";
    std::cin >> k;
    for (int i = 0; i < flights.size(); i++) // Search for that flight number
    {
        if (removeFlightNumber == flights[i].getFlightNumber())
        {
            flights[i].removeAlltheTickets(flights[i].getFlightNumber()); // Call the rem all tickets function for that index
            // flights[i].getAirCraft()->setFlightStatus(false); //Set inFlight as false for that flight's airplane
            //  flights[i].setAirCraft(nullptr); //Set aircraft for that Flight as nullptr

            // for (int j = 0; j < crews.size(); i++)
            // {
            //     if(flights[i].getCrew()->getFlightNumber() == crews[j].getFlightNumber()){
            //         crewJson["crews"][j]["flightNumber"] = "NAN";
            //         ofstream out("crews.json");
            //         out << crewJson;
            //         out.close();
            //     }
            // }

            // flights[i].getCrew()->setFlightNumber("NAN");
            std::string Aeroplane = flights[i].getPlaneID();
            if (k == 0)
            {
                maintainance.writeLandedPlanes(flights[i].getPlaneID(), "add");
            }
            removeFlightObject(flights[i]);
            flights.erase(flights.begin() + i); // remove the flight from vector

            // Json Filing For Flight..

            cout << "Flight has been removed!" << endl;
            return;
        }
    }
    return;
}

void FlightDepartment::displayAvailablePlanes()
{

    bool check = true;

    for (int i = 0; i < airplanes.size(); ++i)
    {
        if (airplanes.at(i).isPlaneAvailable())
        {
            check = false;
            cout << "[" << i + 1 << "] " << airplanes.at(i).getPlaneID() << endl;
        }
    }

    if (check)
    {
        cout << "No Available Airplanes !!" << endl;
        return;
    }
}

void FlightDepartment::crewsMenu()
{
    cout << "Welcome To Crews Menu!" << endl;
    int x;
    do
    {
        cout << "[1]Add Crew, [2]Edit Crew, [3]Assign Crew To Flight, [4]Display All Employees, [5]Display All Crews [0]Exit The Menu: ";

        cin >> x;
        if (x == 1)
        {
            makeNewCrew();
        }
        if (x == 2)
        {
            editCrew();
        }
        if (x == 3)
        {
            assignCrewToFlights();
        }
        if (x == 4)
        {
            displayEmployees();
        }
        if (x == 5)
        {
            displayCrewsOnDemand();
        }
    } while (x != 0);
}

void fun() {}

void FlightDepartment ::loadCrewEmployees()
{
    json crewEmployees;
    //    string filepath = "c:\\Users\\HP\\Desktop\\Programming\\Project\\Testing\\2024-Spring-SE102TB-Project-se102b-e\\Departments\\crewEmployees.json";
    string filepath = "C:\\OOPS_PROJECT_EXTENDED\\2024-Spring-SE102TB-Project-se102b-e\\Departments\\crewEmployees.json";
    ifstream in3(filepath);
    if (!in3.is_open())
    {
        cout << "crewsEmployees.json doesn't exist!" << endl;
        return;
    }

    cout << "Loading From crewsEmployees.json" << endl;
    in3 >> crewEmployees;
    in3.close();

    // cout << "Pilots Size: " << crewEmployees["usedPilots"].size() << endl;
    // cout << pilots[0]->getId() << endl;
    // cout << crewEmployees["usedPilots"][0] << endl;

    for (int i = 0; i < crewEmployees["usedPilots"].size(); i++)
    {
        // cout << "Loop has run for " << i + 1 << " times!" << endl;

        for (int j = 0; j < pilots.size(); j++)
        {
            if (crewEmployees["usedPilots"][i] == pilots[j]->getId())
            {
                // cout << "Pilot Pilot: " << pilots[j]->getId() << endl;
                // cout << "Found used pilot!: " << pilots[j]->getId() << endl;

                usedPilots.push_back(pilots[j]);
                pilots.erase(pilots.begin() + j);
            }
        }
    }

    for (int i = 0; i < crewEmployees["usedMedic"].size(); i++)
    {

        for (int j = 0; j < medics.size(); j++)
        {
            if (crewEmployees["usedMedic"][i] == medics[j]->getId())
            {
                // cout << "Medic Medic: " << medics[j]->getId() << endl;
                // cout << "Found used Medic!: " << medics[j]->getId() << endl;

                usedMedic.push_back(medics[j]);

                medics.erase(medics.begin() + j);
            }
        }
    }

    for (int i = 0; i < crewEmployees["usedFlightAttendants"].size(); i++)
    {
        for (int j = 0; j < flightAttendants.size(); j++)
        {
            if (crewEmployees["usedFlightAttendants"][i] == flightAttendants[j]->getId())
            {
                // cout << "Flight Attendant Flight Attendant: " << flightAttendants[j]->getId() << endl;
                // cout << "Found used Flight Attendant!: " << flightAttendants[j]->getId() << endl;

                usedFlightAttendants.push_back(flightAttendants[j]);
                flightAttendants.erase(flightAttendants.begin() + j);
            }
        }
    }
}

void FlightDepartment ::saveCrewEmployees()
{
    json crewEmployees;
    //    string filepath = "c:\\Users\\HP\\Desktop\\Programming\\Project\\Testing\\2024-Spring-SE102TB-Project-se102b-e\\Departments\\crewEmployees.json";
    string filepath = "C:\\OOPS_PROJECT_EXTENDED\\2024-Spring-SE102TB-Project-se102b-e\\Departments\\crewEmployees.json";

    for (int i = 0; i < usedPilots.size(); i++)
    {
        // cout << "Used Pilot!" << endl;
        crewEmployees["usedPilots"].push_back(usedPilots[i]->getId());
    }

    for (int i = 0; i < usedMedic.size(); i++)
    {
        // cout << "Used Medic!" << endl;
        crewEmployees["usedMedic"].push_back(usedMedic[i]->getId());
    }

    for (int i = 0; i < usedFlightAttendants.size(); i++)
    {
        // cout << "Used flightAttendant!" << endl;
        crewEmployees["usedFlightAttendants"].push_back(usedFlightAttendants[i]->getId());
    }

    ofstream out(filepath);
    out << crewEmployees;
    out.close();
}

void FlightDepartment ::viewVectors()
{
    cout << "Used Pilots!" << endl;
    for (int i = 0; i < usedPilots.size(); i++)
    {
        cout << usedPilots[i]->getId() << " ";
    }
    cout << endl;

    cout << "Used Medic!" << endl;
    for (int i = 0; i < usedMedic.size(); i++)
    {
        cout << usedMedic[i]->getId() << " ";
    }
    cout << endl;

    cout << "Used Flight Attendants!" << endl;
    for (int i = 0; i < usedFlightAttendants.size(); i++)
    {
        cout << usedFlightAttendants[i]->getId() << " ";
    }
    cout << endl;
}

void FlightDepartment::incrementAndDecrementOfAvailableSeats(int index)
{
    // cout<<"Before loop.\n";
    for (int i = 0; i < jsonFlights.size(); i++)
    {
        // cout<<"Before iff.\n";

        if (flights[index].getFlightNumber() == jsonFlights[i]["flightNumber"])
        {
            // cout<<"Before after.\n";

            flights[index].getAvailableSeats() == jsonFlights[i]["availableSeats"];
        }
        // cout<<"after loop.\n";
    }
    // cout<<"after loop2.\n";

    //    ofstream out("C:\\Users\\Scorp Radoz\\Documents\\GitHub\\2024-Spring-SE102TB-Project-se102b-e\\Departments\\flights.json" ,ios::trunc);
    ofstream out("C:\\OOPS_PROJECT_EXTENDED\\2024-Spring-SE102TB-Project-se102b-e\\Departments\\flights.json", ios::trunc);
    if (out.is_open())
    {
        // cout<<"file open.\n";
    }
    out << jsonFlights;
    out.close();
}

void FlightDepartment::adminEnd(AirplaneMaintenance &maintainance)
{
    int x;
    do
    {
        std::cout << "Enter :-\n [1] to add the flight.\n[2] to veiw crew functionality.\n[3] to remove the fliht.\n[4] to view the ongoing flights.\n[5] to exit the menu.\n";
        std::cin >> x;
        switch (x)
        {
        case 1:
            addFlight();
            break;
        case 2:
        {
            crewsMenu();
        }
        case 3:
        {
            removeFlight(maintainance);
        }
        case 4:
        {
            displayFlights();
        }
        default:
            break;
        }

    } while (x != 5);
}

void FlightDepartment ::removeFlightObject(Flight &flight)
{
    for (int i = 0; i < jsonFlights.size(); i++)
    {
        if (flight.getFlightNumber() == jsonFlights[i]["flightNumber"])
        {
            jsonFlights.erase(i);
        }
    }
    //    ofstream out("C:\\Users\\Scorp Radoz\\Documents\\GitHub\\2024-Spring-SE102TB-Project-se102b-e\\Departments\\flights.json" ,ios::trunc);
    ofstream out("C:\\OOPS_PROJECT_EXTENDED\\2024-Spring-SE102TB-Project-se102b-e\\Departments\\flights.json", ios::trunc);
    out << jsonFlights;
    out.close();
}

void FlightDepartment ::displayEmployees()
{
    json loadData;
    int total = 0;
    loadCrews(loadData, total);
    cout << pilots.size() << endl;
    displayCrewTemplate("Idle Pilots/ Co-Pilots", pilots);
    displayCrewTemplate("Idle Medics/ Pursers", medics);
    displayCrewTemplate("Idle Flight Attendants", flightAttendants);
    displayCrewTemplate("Used Pilots/ Co-Pilots", usedPilots);
    displayCrewTemplate("Used Medics/ Pursers", usedMedic);
    displayCrewTemplate("Used Flight Attendants", flightAttendants);
}

template <typename T>
void FlightDepartment ::displayCrewTemplate(string type, vector<T> employees)
{

    cout << "Displaying: " << type << endl;
    for (int i = 0; i < employees.size(); i++)
    {
        cout << "ID: " << employees[i]->getId() << endl;
    }
}

void FlightDepartment::receivePilots(vector<Pilot *> pilotsVector, vector<FlightAttendant *> flightVector, vector<Medic *> medicVector)
{
    pilots = pilotsVector;
    flightAttendants = flightVector;
    medics = medicVector;
}

void FlightDepartment ::displayCrewsOnDemand()
{

    for (int i = 0; i < crews.size(); i++)
    {
        cout << crews[i] << endl;
    }
}