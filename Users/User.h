#ifndef _USER_H_
#define _USER_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <typeinfo>
#include <unistd.h>
#include <sstream>
#include "../nlohmann/json.hpp"
using json = nlohmann ::json;

class User 
{
protected: 
    std::string firstName, lastName, id, pass;
public:

    // Constructors
    User();
    User(const std::string&, const std::string&, const std::string&, const std::string&);
    virtual ~User () = default;

    // Getters
    std::string getFirstName () const;
    std::string getLastName () const;
    std::string getId () const;
    std::string getPass () const;
    
    // login function
    virtual bool login (const std::string&, const std::string&) const = 0;
    virtual void displayInfo() const = 0;

    // friends
    friend std::istream& operator >> (std::istream& is, User& user);
    friend std::ostream& operator << (std::ostream& os, const User& user);
};


#endif // User Abstract class