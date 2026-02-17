//
// Created by lenovo on 4/7/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_ADDRESS_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_ADDRESS_H
#include<iostream>
using namespace std;
#include <vector>
class Address {
    string country;
    string district;
    string city;
    string street;
    string houseNo;
    string nearAirport;
public:
    Address();
    Address(string nearAirport,string country,string dist,string ci,string stNo,string hNO);
    string getCountry() ;
    void setCountry( string newCountry);
    string getNearAirport();
    void setNearAirport(string NearAirport);
    string getDistrict() ;
    void setDistrict(string newDistrict);
    string getCity();

    void setCity( string newCity);

    string getStreet();
    void setStreet(string newStreet);
    string getHouseNo();

    void setHouseNo( string newHouseNo);
};


#endif //INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_ADDRESS_H
