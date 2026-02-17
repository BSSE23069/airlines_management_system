//
// Created by lenovo on 4/7/2024.
//

#include "Receiver.h"
using namespace std;
Receiver::Receiver(){
    receive=false;
    name="";
    age=0;
    cnic=0;
    contactNo=0;
}
//setter function for attributes

bool Receiver:: getReceive(){
    return receive;
}
void Receiver:: setReceive(bool Receive){
    this->receive=Receive;
}
void Receiver:: setName(string newName) {
    name = newName;
}

void Receiver::setAge(int newAge) {
    age = newAge;
}

void Receiver::setCnic(int newCnic) {
    cnic = newCnic;
}

void Receiver::setContactNo(int newContactNo) {
    contactNo = newContactNo;
}
//getter function for attributes
string Receiver:: getName() const {
    return name;
}

int Receiver::getAge()  {
    return age;
}

int Receiver:: getCnic()  {
    return cnic;
}

int Receiver::getContactNo() {
    return contactNo;
}
void Receiver::receiverAddress(){  //for address of receiver
    string country;
    string district;
    string city;
    string street;
    string houseNo;
    cout<<"enter country name: "<<endl;
    cin>>country;
    cout<<"enter district name: "<<endl;
    cin>>district;
    cout<<"enter city name: "<<endl;
    cin>>city;
    cout<<"enter street number: "<<endl;
    cin>>street;
    cout<<"enter houseNO: "<<endl;
    cin>>houseNo;
    add.setCountry(country);
    add.setCity(city);
    add.setDistrict(district);
    add.setStreet(street);
    add.setHouseNo(houseNo);
}
nlohmann:: json Receiver:: makeRecord() {
    ifstream n("cargoCompany/courier.json");
    if (!n.is_open()) {
        cout << "not open";
//        json empty;
//        return empty;

    }
    nlohmann::json n1;
    if(!n.is_open()){
        cout << "File not found!" << endl;
    }
    n >> n1;
    return n1;
}
void Receiver:: PutInfo() {
    nlohmann::json courier= makeRecord();
    string name;
    int age;
    int nic;
    int contractNo;
    cout << "enter Receiver name: " << endl;
    cin >> name;
    cout << "enter age: " << endl;
    cin >> age;
    cout << "enter NIC: " << endl;
    cin >> nic;
    cout << "enter contract Number: " << endl;
    cin >> contractNo;
    nlohmann::  json receiverInfo;
    receiverInfo["ReceiverName"] = name;
    receiverInfo["ReceiveAge"] = age;
    receiverInfo["ReceiveCNIC"] = nic;
    receiverInfo["contractNo"] = contractNo;
    receiverInfo["country"] = add.getCountry();
    receiverInfo["city"] = add.getCity();
    receiverInfo["district"] = add.getDistrict();
    receiverInfo["street"] = add.getStreet();
    receiverInfo["houseNo"] = add.getHouseNo();
    receiverInfo["receiving status"] ;
    courier["receiver"].push_back(receiverInfo);
    ofstream out("courier.json");
    out << courier;
    out.close();
}
