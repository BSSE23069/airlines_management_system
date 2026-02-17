//
// Created by lenovo on 4/7/2024.
//

#include "Sender.h"
using namespace std;
Sender::Sender(){
    send=false;
    name="";
    age=0;
    cnic=0;
    totalPrice=0.0;
    count=0;
    contactNo=0;
    luggagePrice=0.0;
    distance=0.0;
}
void Sender:: setName(string newName) {
    name = newName;
}

void Sender:: setAge(int newAge) {
    age = newAge;
}
void Sender::setStatus(bool Send){
    this->send=Send;
}
bool  Sender:: getStatus(){
    return send;
}
void  Sender::setCnic(int newCnic) {
    cnic = newCnic;
}

void  Sender::setContactNo(int newContactNo) {
    contactNo = newContactNo;
}

void  Sender::setLuggagePrice(double newLuggagePrice) {
    luggagePrice = newLuggagePrice;
}

// Getter functions
string  Sender:: getName() const {
    return name;
}

int Sender:: getAge()  {
    return age;
}

int  Sender::getCnic()  {
    return cnic;
}

int  Sender::getContactNo() {
    return contactNo;
}

double  Sender:: getLuggagePrice(){
    return luggagePrice;
}
nlohmann:: json Sender:: makeRecord() {
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
void Sender::senderAddress(){
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
void  Sender:: PutInfo( ) {
    nlohmann::json courier= makeRecord();
    string name;
    int age;
    int price;
    int nic;
    int contactNo;
    cout << "Enter sender name: ";
    cin >> name;
    cout << "Enter age: ";
    cin >> age;
    cout << "Enter NIC: ";
    cin >> nic;
    cout << "Enter contract number: ";
    cin >> contactNo;
    senderAddress();
    nlohmann::json senderInfo;
    senderInfo["senderName"] = name;
    senderInfo["senderAge"] = age;
    senderInfo["senderNic"] = nic;
    senderInfo["contactNo"] = contactNo;
    senderInfo["country"] = add.getCountry();
    senderInfo["city"] = add.getCity();
    senderInfo["district"] = add.getDistrict();
    senderInfo["street"] = add.getStreet();
    senderInfo["houseNo"] = add.getHouseNo();
    senderInfo["sending status"] = getStatus();
    courier["sender"].push_back(senderInfo);
    ofstream out("courier.json");
    out << courier;
    out.close();
}

void  Sender::find(  nlohmann::json& courier) {
    courier= makeRecord();
    string name;
    cin >> name;
    for (int i = 0; i < courier.size(); i++) {
        if (name == courier["sender"][i]["senderName"]) {
            cout << "name found" << endl;
            cout << courier["sender"][i]["senderAge"];
            cout << courier["sender"][i]["senderNic"];
            cout << courier["sender"][i]["contactNO"];
        }
    }
}
double  Sender:: toRadians(double degrees) {
    return degrees * 3.14159265358979323846 / 180.0;
}

double Sender:: calculateDistance() {
    double lat1;
    double lon1;
    double lat2;
    double lon2;
    cout<<"enter latitude of sending area: "<<endl;
    cin>>lat1;
    cout<<"enter longitude of sending area: "<<endl;
    cin>>lon1;
    cout<<"enter latitude of receiving area: "<<endl;
    cin>>lon2;
    cout<<"enter longitude of receiving area: "<<endl;
    cin>>lat2;
    lat1 = toRadians(lat1);
    lon1 = toRadians(lon1);
    lat2 = toRadians(lat2);
    lon2 = toRadians(lon2);
    double x = (lon2 - lon1) * cos((lat1 + lat2) / 2.0);
    double y = lat2 - lat1;
    distance = sqrt(x * x + y * y) * 6371.0;
    cout<<" "<<distance;
    return distance;
}

void Sender:: packageInfo(  nlohmann::json& senderInfo) {
                    calculateDistance();
                    int date;
                    time_t now = time(nullptr);
                    tm* ti = localtime(&now);
                    date = ti->tm_mday;
                    senderInfo= makeRecord();
                    int type;
                    int c;
                    Items newItem[10];
                    double weights;
                    cout << "enter how many Items you have" << endl;
                    cin >> c;
                    count = c;
                    for (int i = 0; i < count; i++) {
                        cout << "enter weight of item: " << endl;
                        cin >> weights;
                        newItem[i].weight = weights;
                        newItem[i].id = name+ to_string(i);
                        cout << "enter type 1 for sensitive 2 for electronics 3 for mix: " << endl;
                        cin >> type;
                        {
                            if (type == 1) {
                                newItem[i].price = distance * weights * 40;
                                totalPrice += newItem[i].price;
                            } else if (type == 2) {
                                newItem[i].price = distance * weights * 37;
                                totalPrice += newItem[i].price;
                            } else if (type == 3) {
                newItem[i].price = distance * weights * 35.5;
                totalPrice += newItem[i].price;
            } else {
                cout << "does not match" << endl;
            }
        }
        if(date>=28 && add.getCountry()!=add.getCountry())
        {
            cout<<"congratulation you won 20 percent discount for international transfer"<<endl;
                        totalPrice=totalPrice-totalPrice/20;
        }
        if(date>=25 && add.getCountry()==add.getCountry()){
            cout<<"congratulation you won 10 percent discount for international transfer"<<endl;
            totalPrice=totalPrice-totalPrice/10;
        }
        else
        {
            cout<<endl;
        }
        for(int j=0;j<senderInfo["sender"].size();j++){
            if(senderInfo["sender"][j]["senderName"]==getName()){
                senderInfo["sender"][j]["price"]=totalPrice;
                senderInfo["sender"][j]["no of items"] = count;

                for(int i=0;i<count;i++){
                senderInfo["sender"][j]["id"][i] = newItem[i].id;
                senderInfo["sender"][j]["weight"][i]=newItem[i].weight;
                }
            }
        }
      //a1.removeBalance(total);


    }
    
    i1.push_back(newItem[count]);
    ofstream out("courier.json");
    out << senderInfo;
    out.close();
}