#include "Address.h"

// Default constructor definition
Address::Address() {
  nearAirport = "";
  country = "";
  district = "";
  city = "";
  street = "";
  houseNo = "";
}

// Parameterized constructor definition
Address::Address(std::string nearAirport, std::string country, std::string district, std::string city, std::string street, std::string houseNo) {
  this->country = country;
  this->nearAirport = nearAirport;
  this->district = district;
  this->city = city;
  this->street = street;
  this->houseNo = houseNo;
}

// Getter and setter method definitions
std::string Address::getCountry() {
  return country;
}
void Address::setCountry(std::string newCountry) {
  country = newCountry;
}
std::string Address::getNearAirport() {
  return nearAirport;
}
void Address::setNearAirport(std::string NearAirport) {
  nearAirport = NearAirport;
}
std::string Address::getDistrict() {
  return district;
}
void Address::setDistrict(std::string newDistrict) {
  district = newDistrict;
}
std::string Address::getCity() {
  return city;
}
void Address::setCity(std::string newCity) {
  city = newCity;
}
std::string Address::getStreet() {
  return street;
}
void Address::setStreet(std::string newStreet) {
  street = newStreet;
}
std::string Address::getHouseNo() {
  return houseNo;
}
void Address::setHouseNo(std::string newHouseNo) {
  houseNo = newHouseNo;
}
