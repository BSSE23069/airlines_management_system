#include "User.h"

User ::User() : User ("None", "None", "None", "None")
{
    
}

User :: User(const std::string& first, const std::string& last, const std::string& id,  const std::string& pass) 
    :   firstName(first), lastName(last), id(id), pass(pass)
{
     
}

// Getters
std::string User :: getFirstName () const{
    return firstName;
}

std::string User :: getLastName () const{
    return lastName;
}

std::string User :: getId () const{
    return id;
}

std::string User :: getPass () const{
    return pass;
}


// Friends
std::istream &operator>>(std::istream &is, User &user)
{
    std ::cout << "\nEnter Id: ";
    is >> user.id;
    std ::cout << "\nEnter password: ";
    is >> user.pass;
    return is;
}


std::ostream &operator<<(std::ostream &os, const User &user)
{
    os << "\n First name : " << user.firstName << "\n Last name  : " << user.lastName << "\n Id         : " << user.id << "\n Password   : " << user.pass << std::endl;
    return os;
}


// No Implementation required for the pure virtual function login ()