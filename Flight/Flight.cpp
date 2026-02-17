//
// Created by Scorp Radoz on 21/04/2024.
//

#include "Flight.h"

Flight::Flight(const std::string &departure, const std::string &destination,
               const std::string &flightNumber /*, int *facilities*/) : departure(departure), destination(destination), flightNumber(flightNumber) /*, facilities(facilities) */
{
    crew = nullptr;
    aircraft = nullptr;
    // readBookedTicketsFromJson();
    //  readTicketFromJson();

    std::ifstream file("C:\\OOPS_PROJECT_EXTENDED\\2024-Spring-SE102TB-Project-se102b-e\\Flight\\tickets.json");

    if (!file.is_open())
    {
        cout << "" << endl;
    }

    // Check if the file is empty
    if (file.peek() == ifstream::traits_type::eof())
    {
        cout << "" << endl;
    }
    else
    {
        file >> jsonTickets;
    }
    file.close();
    for (int i = 0; i < jsonTickets.size(); i++)
    {
        std::string temp = "nan";
        Ticket ticket(temp, temp, temp, temp, temp);
        ticket.setCustomerId(jsonTickets[i]["customerId"]);
        ticket.setPassengerName(jsonTickets[i]["passengerName"]);
        ticket.setPassengerAge(jsonTickets[i]["passengerAge"]);
        ticket.setCNIC(jsonTickets[i]["CNIC"]);
        ticket.setDeparture(jsonTickets[i]["departure"]);
        ticket.setDestination(jsonTickets[i]["destination"]);
        ticket.setFlightNumber(jsonTickets[i]["flightNumber"]);
        ticket.setSeatNumber(jsonTickets[i]["seatNumber"]);
        ticket.setDepartureTime(jsonTickets[i]["departureTime"]);
        ticket.setDestinationTime(jsonTickets[i]["destinationTime"]);
        if (ticket.readingTicket(departureTime, arrivalTime, departure, destination, planeID))
            tickets.push_back(ticket);
    }

    std::ifstream booked("C:\\OOPS_PROJECT_EXTENDED\\2024-Spring-SE102TB-Project-se102b-e\\Flight\\Bookedtickets.json");

    if (!booked.is_open())
    {
        cout << "" << endl;
    }

    // Check if the file is empty
    if (booked.peek() == ifstream::traits_type::eof())
    {
        cout << "" << endl;
    }
    else
    {
        booked >> jsonTickets;
    }

    booked.close();

    for (int i = 0; i < jsonBookedTickets.size(); i++)
    {
        std::string temp = "nan";
        BookedTickets ticket(temp, temp, temp, temp, temp);
        ticket.setCustomerId(jsonBookedTickets[i]["customerId"]);
        ticket.setPassengerName(jsonBookedTickets[i]["passengerName"]);
        ticket.setPassengerAge(jsonBookedTickets[i]["passengerAge"]);
        ticket.setCNIC(jsonBookedTickets[i]["CNIC"]);
        ticket.setDeparture(jsonBookedTickets[i]["departure"]);
        ticket.setDestination(jsonBookedTickets[i]["destination"]);
        ticket.setFlightNumber(jsonBookedTickets[i]["flightNumber"]);
        ticket.setSeatNumber(jsonBookedTickets[i]["seatNumber"]);
        ticket.setDepartureTime(jsonBookedTickets[i]["departureTime"]);
        ticket.setDestinationTime(jsonBookedTickets[i]["destinationTime"]);
        ticket.setPrice(jsonBookedTickets[i]["price"]);
        ticket.setBookingTime(jsonBookedTickets[i]["bookingTime"]);
        ticket.setIsPaid(jsonBookedTickets[i]["isPaid"]);
        if (ticket.readingTicket(departureTime, arrivalTime, departure, destination, planeID))
            bookedTickets.push_back(ticket);
    }
}

Ticket Flight::buySeat(std::string customerID)
{
    checkBookingTime();
    aircraft->displaySeats();
    std::string number;
    std::cout << "Enter the seat Number you want to reserve or enter [0] to not reserve.\n";
    std::cin >> number;
    if (number != "0")
    {
        aircraft->setSeat(number, true);
        Ticket ticket(customerID, departure, destination, flightNumber, number);
        //        std::cin >> ticket;
        if (inputDetails(ticket))
        {
            ticket.setDepartureTime(departureTime);
            ticket.setDestinationTime(arrivalTime);
            tickets.push_back(ticket);
            writeTicketsToJson(ticket);
            Account account;
            std::cout << "Enter the Account Number you want to pay the money through : ";
            std::string accountNo;
            std::cin.ignore();
            std::cin >> accountNo;
            double price = aircraft->getSeatPrice(number);
            account.removeBalanceDirectly(accountNo, price);
            std::cout<< "You have successfully reserved the seat.\n";
            --availableSeats;
            return ticket;
        }
        else
        {
            aircraft->setSeat(number, false);
        }
    }

    std::string temporary = "NAN";
    Ticket ticket(temporary, temporary, temporary, temporary, temporary);
    return ticket;
}

void Flight::setSeatPrice(double hours)
{
    aircraft->setSeatPrice(hours);
}

BookedTickets Flight::bookSeat(std::string customerID)
{
    checkBookingTime();
    aircraft->displaySeats();
    std::string number;
    std::cout << "Enter the seat Number you want to book or enter [0] to not book.\n";
    std::cin >> number;
    if (number != "0")
    {
        aircraft->setSeat(number, true);
        BookedTickets newBookedTicket(customerID, departure, destination, flightNumber, number);
        if (inputDetails(newBookedTicket))
        {
            newBookedTicket.setDepartureTime(departureTime);
            newBookedTicket.setDestinationTime(arrivalTime);
            newBookedTicket.setBookingTime(time(nullptr));
            newBookedTicket.setPrice(aircraft->getSeatPrice(number));
            newBookedTicket.setIsPaid(false);
            // std::cin >> newBookedTicket;//Booking time gets stored inside the >> operator
            writeBookedTicketsToJson(newBookedTicket);
            bookedTickets.push_back(newBookedTicket); // Store the new booked ticket in the booked tickets of this flight
            std::cout << "You have successfully reserved the seat.\n";
            --availableSeats;
            return newBookedTicket; // Return the newly booked ticket
        }
        else
        {
            aircraft->setSeat(number, false);
        }
    }
    std::string temporary = "NAN";
    BookedTickets newBookedTicket(temporary, temporary, temporary, temporary, temporary);
    return newBookedTicket;
}

void Flight::checkBookingTime()
{ // Check the booking time of all the booked tickets

    time_t now = time(nullptr); // Calculate the current time

    for (int i = 0; i < bookedTickets.size(); i++)
    {
        time_t comparedTime = difftime(now, bookedTickets[i].getBookingTime());
        if (comparedTime >= 3600)
        { // Check if time is greater than or equal to 2 minutes

            if (bookedTickets[i].getIsPaid() == false)
            {
                aircraft->setSeat(bookedTickets[i].getSeatNumber(),
                                  false); // Set the seat of this ticket -> Availability = true
                removeBookedTicket(bookedTickets[i]);
                ++availableSeats;
                bookedTickets.erase(bookedTickets.begin() + i); // Removed the ticket from the class Flight
                cout << "Ticket of flight# " << flightNumber << " issued against seat number# "
                     << bookedTickets[i].getSeatNumber()
                     << " has been cancelled because of surpassing of booking limitation time." << endl;
            }
            else if (bookedTickets[i].getIsPaid() == true)
            {

                Ticket ticket(bookedTickets[i]);
                writeTicketsToJson(ticket);
                tickets.push_back(ticket);
                removeBookedTicket(bookedTickets[i]);
                bookedTickets.erase(bookedTickets.begin() + i);
            }
        }
    }
}

void Flight::readFlight(json j)
{
    departure = j["departure"];
    departureTime = j["departureTime"];
    availableSeats = j["availableSeats"];
    arrivalTime = j["arrivalTime"];
    destination = j["destination"];
    flightNumber = j["flightNumber"];
    planeID = j["planeID"];
}

void Flight::setArrival()
{
    int i = 0;
    bool ok;
    do
    {
        std::string s;
        if (i != 0)
        {
            std::cout << "Enter the departure time in the format : YYYY-MM-DD HH:MM:SS  e.g 2024-04-24 19:33:37\n";
        }
        std::getline(std::cin, s);
        ok = setArrivalAndDeparture(s);
        i++;
    } while (!ok);
}

bool Flight::setArrivalAndDeparture(std::string &s)
{
    static int j = 0;
    std::tm t = {};
    // std::string s = "2024-04-24 19:33:37"; // your date-time string
    int numItemsScanned = sscanf(s.c_str(), "%d-%d-%d %d:%d:%d", &t.tm_year, &t.tm_mon, &t.tm_mday, &t.tm_hour,
                                 &t.tm_min, &t.tm_sec);

    if (numItemsScanned != 6)
    {
        if (j != 0)
        {
            std::cout << "Invalid date-time string format. Please use 'YYYY-MM-DD HH:MM:SS'." << std::endl;
        }
        j++;
        return false;
    }

    t.tm_year -= 1900; // Year since 1900
    t.tm_mon--;        // Months since January (0-11)

    std::time_t timeSinceEpoch = std::mktime(&t);

    if (timeSinceEpoch == -1)
    {
        std::cout << "Invalid date-time values." << std::endl;
        return false;
    }

    std::cout << "Enter the flight hours.\n";
    double hours;
    std::cin >> hours;
    departureTime = timeSinceEpoch;
    arrivalTime = timeSinceEpoch + (hours * 3600);
    aircraft->setSeatPrice(hours);
    return true;
}

void Flight::displayFlight()
{
    std::cout << "Flight Number : " << flightNumber << "\n";
    std::cout << "Departure : " << departure << "\n";
    std::cout << "Departure Time : " << ctime(&departureTime) << "\n";
    std::cout << "Destination : " << destination << "\n";
    std::cout << "Arrival time : " << ctime(&arrivalTime) << "\n";
    std::cout << "Available Seats : " << availableSeats << "\n";
    std::cout << "================================================\n";
}

std::string Flight::getDeparture()
{
    return this->departure;
}

std::string Flight::getDestination()
{
    return this->destination;
}

std::string Flight::getFlightNumber()
{
    return this->flightNumber;
}

bool Flight::checkBookedTicket(BookedTickets &ticket)
{
    for (int i = 0; i < bookedTickets.size(); i++)
    {
        if (bookedTickets[i] == ticket)
        {
            bookedTickets[i].setIsPaid(true);
            Ticket ticket1(bookedTickets[i]);
            writeTicketsToJson(ticket1);
            tickets.push_back(ticket1);
            removeBookedTicket(bookedTickets[i]);
            bookedTickets.erase(bookedTickets.begin() + i);
            return true;
        }
    }
    return false;
}

void Flight::setAirplane(Airplane &airplane)
{
    aircraft = &airplane;
    planeID = airplane.getPlaneID();
}

void Flight::writeTicketsToJson(Ticket &ticket)
{
    nlohmann::json j;
    nlohmann::json ticketJson;
    ticketJson["customerId"] = ticket.getCustomerId();
    ticketJson["passengerName"] = ticket.getPassengerName();
    ticketJson["passengerAge"] = ticket.getPassengerAge();
    ticketJson["CNIC"] = ticket.getCNIC();
    ticketJson["departure"] = ticket.getDeparture();
    ticketJson["destination"] = ticket.getDestination();
    ticketJson["flightNumber"] = ticket.getFlightNumber();
    ticketJson["seatNumber"] = ticket.getSeatNumber();
    ticketJson["departureTime"] = ticket.getDepartureTime();
    ticketJson["destinationTime"] = ticket.getDestinationTime();

    jsonTickets.push_back(ticketJson);

    std::ofstream file("Flight\\tickets.json");
    file << jsonTickets;
    file.close();
}

void Flight::writeBookedTicketsToJson(BookedTickets &ticket)
{

    //    std::string temp="nan";
    //    BookedTickets ticket(temp,temp,temp,temp);
    nlohmann::json ticketJson;
    ticketJson["customerId"] = ticket.getCustomerId();
    ticketJson["passengerName"] = ticket.getPassengerName();
    ticketJson["passengerAge"] = ticket.getPassengerAge();
    ticketJson["CNIC"] = ticket.getCNIC();
    ticketJson["departure"] = ticket.getDeparture();
    ticketJson["destination"] = ticket.getDestination();
    ticketJson["flightNumber"] = ticket.getFlightNumber();
    ticketJson["seatNumber"] = ticket.getSeatNumber();
    ticketJson["departureTime"] = ticket.getDepartureTime();
    ticketJson["destinationTime"] = ticket.getDestinationTime();
    ticketJson["price"] = ticket.getPrice();
    ticketJson["bookingTime"] = ticket.getBookingTime();
    ticketJson["isPaid"] = ticket.getIsPaid();
    jsonBookedTickets.push_back(ticketJson);

    std::ofstream file("Flight\\Bookedtickets.json");
    file << jsonBookedTickets;
    file.close();
}

void Flight::removeAlltheTickets(std::string ID)
{

    for (int i = 0; i < jsonTickets.size(); i++)
    {
        if (jsonTickets[i]["flightNumber"] == ID)
        {
            jsonTickets.erase(i);
        }
    }
    ofstream fileOut("Flight\\tickets.json");
    fileOut << jsonTickets;
    fileOut.close();

    for (int i = 0; i < jsonBookedTickets.size(); i++)
    {
        if (jsonBookedTickets[i]["flightNumber"] == ID)
        {
            jsonBookedTickets.erase(i);
        }
    }
    ofstream fileOutBooked("Flight\\Bookedtickets.json");
    fileOut << jsonBookedTickets;
    fileOut.close();
}

void Flight::removeBookedTicket(BookedTickets &ticket)
{

    for (int i = 0; i < jsonBookedTickets.size(); i++)
    {
        if (jsonBookedTickets[i]["flightNumber"] == ticket.getFlightNumber() &&
            jsonBookedTickets[i]["seatNumber"] == ticket.getSeatNumber())
        {
            jsonBookedTickets.erase(i);
        }
    }
    ofstream fileOutBooked("Flight\\Bookedtickets.json");
    fileOutBooked << jsonBookedTickets;
    fileOutBooked.close();
}

Airplane *Flight::getAirCraft()
{
    return aircraft;
}

Crew *Flight::getCrew()
{
    return crew;
}

void Flight::setCrew(Crew value)
{
    crew = &value;
}

void Flight::displayBookedAndNormalSeats()
{
    int x;
    do
    {
        std::cout
            << "Enter [1] the passengers of the bought seats,[2] to display the passengers of the booked seats,[3] to exit.\n";
        std::cin >> x;
        switch (x)
        {
        case 1:
        {
            for (int i = 0; i < tickets.size(); ++i)
            {
                std::cout << tickets[i];
            }
            break;
        }
        case 2:
        {
            for (int i = 0; i < bookedTickets.size(); ++i)
            {
                std::cout << bookedTickets[i];
            }
            break;
        }
        case 3:
        {
            std::cout << "Bye.\n";
            break;
        }
        default:
        {
            std::cout << "Invalid Input.\n";
        }
        }
    } while (x != 3);
}

bool Flight::isCNICav(std::string CNIC)
{
    int j = 0;
    for (int i = 0; i < tickets.size(); i++)
    {
        std::cout << CNIC << " " << tickets[i].getCNIC() << std::endl;
        if (CNIC == tickets[i].getCNIC())
        {
            j++;
        }
    }
    for (int i = 0; i < bookedTickets.size(); i++)
    {
        std::cout << CNIC << " " << bookedTickets[i].getCNIC() << std::endl;
        if (CNIC == bookedTickets[i].getCNIC())
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

bool Flight::inputDetails(Ticket &ticket)
{
    bool cnic;
    int x;
    std::string CNIC;
    ticket.addPassengerName();
    ticket.addPassengerAge();
    do
    {
        std::cout << "Enter the CNIC of the passenger : ";
        std::getline(std::cin, CNIC);
        cnic = isCNICav(CNIC);
        ticket.setCNIC(CNIC);
        if (!cnic)
        {
            std::cout << "You cannot use the same CNIC for multiple seats.\nEnter [0] to stop the process or [1] or to use different CNIC.\n";
            std::cin >> x;
        }
        else
        {
            x = 0;
        }
    } while (x != 0);
    if (cnic)
    {
        return true;
    }
    return false;
}

int Flight::getAvailableSeats()
{
    return availableSeats;
}
