#include "Customer.h"

Customer ::Customer() : User("", "", "", "")
{
}

// Customer(const std::string & id, const std::string &pass) :
Customer ::Customer(const std::string &first, const std::string &last, const std::string &id, const std::string &pass)
        : User(first, last, id, pass)
{
// std::ifstream file("C:\\Users\\Scorp Radoz\\Documents\\GitHub\\2024-Spring-SE102TB-Project-se102b-e\\Customers\\Customertickets.json");
 std::ifstream file("C:\\OOPS_PROJECT_EXTENDED\\Super-Duper-Private-Group-Code\\Customers\\Customertickets.json");


    if (!file.is_open()) {
        std::cout<< "\n";
    }

// Check if the file is empty
    if (file.peek() == ifstream::traits_type::eof()) {
        std::cout<< "\n";
    } else {
        file >> jsonTickets;
    }
    file.close();
    for (int i = 0; i < jsonTickets.size(); i++) {
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
        if (ticket.getCustomerId()==jsonTickets[i]["customerId"])
            tickets.push_back(ticket);
    }

//    std::ifstream booked("C:\\Users\\Scorp Radoz\\Documents\\GitHub\\2024-Spring-SE102TB-Project-se102b-e\\Customers\\CustomerBookedtickets.json");
    std::ifstream booked("C:\\OOPS_PROJECT_EXTENDED\\Super-Duper-Private-Group-Code\\Customers\\CustomerBookedtickets.json");

    if (!booked.is_open()) {
        std::cout<< "\n";
    }

// Check if the file is empty
    if (booked.peek() == ifstream::traits_type::eof()) {
        std::cout<< "\n";


        } 
        
    else {
        booked >> jsonTickets;
    }
    booked.close();

    for (int i=0;i<jsonBookedTickets.size();i++) {
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
        if (ticket.getCustomerId()==jsonTickets[i]["customerId"]){
            bookedTickets.push_back(ticket);
        }
    }

}

bool Customer ::login(const std::string &id, const std::string &pass) const
{
    if (this->id == id && this->pass == pass)
        return true;
    return false;
}

void Customer::addTicket(Ticket ticket){
    tickets.push_back(ticket);
    writeTicketsToJson(ticket);


}
void Customer::addBookedTicket(BookedTickets ticket){
    bookedTickets.push_back(ticket);
    writeBookedTicketsToJson(ticket);
}

BookedTickets Customer::payPriceOfTickets() {
    int k=0;
    std::cout<<""<<bookedTickets.size();
    for (int i = 0; i < bookedTickets.size(); ++i) {
        time_t now= time(nullptr);

        
        if (!bookedTickets[i].getIsPaid() && now< (bookedTickets[i].getBookingTime() + 3600)/*  +some value */ ) {
            std::cout << "Ticket Number : " << i + 1 << "\n";
            std::cout << bookedTickets[i];
            k++;
       }
    }
    if(k!=0){
    std::cout<<"Enter the Index of the ticket you want to pay the price of : ";
    int i;
    std::cin>>i;
    return bookedTickets[i-1];
    }
    string temp="NAN";
    BookedTickets temps(temp,temp,temp,temp,temp);
    return temps;
}

void Customer::addTicketAfterPayingPrice(BookedTickets &ticket) {
    for (int i = 0; i < bookedTickets.size(); ++i) {
        if(bookedTickets[i]==ticket){
            bookedTickets[i].setIsPaid(true);
            Ticket ticket1(bookedTickets[i]);
            addTicket(ticket1);
            removeBookedTicket(bookedTickets[i]);
            bookedTickets.erase(bookedTickets.begin()+i);
        }
    }
}

void Customer::displayTicketsHistory(){
    for(int i=0;i<tickets.size();i++){
    std::cout<<tickets[i];
    }
}

void  Customer::writeTicketsToJson(Ticket &ticket) {
    nlohmann::json ticketJson;
    ticketJson["customerId"]=ticket.getCustomerId();
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

    std::ofstream file("Customers\\Customertickets.json");
    file << jsonTickets;
    file.close();
}

void Customer::writeBookedTicketsToJson(BookedTickets &ticket) {
//    std::string temp="nan";
//    BookedTickets ticket(temp,temp,temp,temp);
    nlohmann::json ticketJson;
    ticketJson["customerId"]=ticket.getCustomerId();
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

    std::ofstream file("Customers\\CustomerBookedtickets.json");
    file << jsonBookedTickets;
    file.close();
}

void Customer :: removeBookedTicket(BookedTickets & ticket) {
   
    for (int i = 0; i < jsonBookedTickets.size(); i++) {
        if (jsonBookedTickets[i]["flightNumber"] == ticket.getFlightNumber() &&
            jsonBookedTickets[i]["seatNumber"] == ticket.getSeatNumber() && jsonBookedTickets[i]["bookingTime"]==ticket.getBookingTime() && jsonBookedTickets[i]["customerId"]==ticket.getCustomerId()) {
            jsonBookedTickets.erase(i);
        }
    }
    ofstream fileOutBooked("Customers\\CustomerBookedtickets.json");
    fileOutBooked << jsonBookedTickets;
    fileOutBooked.close();
}


void Customer :: displayInfo() const 
{
    std::cout << *this << std::endl;
}

std::ostream& operator << (std::ostream& os, const Customer& cus)
{
    os << "FirstName: " << cus.firstName << std::endl;
    os << "lastName : " << cus.lastName  << std::endl;
    os << "User Id  : " << cus.id << std::endl;
    os << "Password : " << cus.pass << std::endl;
    return os;
}
