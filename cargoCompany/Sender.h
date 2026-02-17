//
// Created by lenovo on 4/7/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_SENDER_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_SENDER_H
using namespace std;
#include <vector>
#include "Person.h"
#include "json.hpp"
#include <fstream>
#include "Items.h"
#include "Address.h"
class Sender: public Person{
  bool send;
  double luggagePrice;
  float totalPrice;
  int count;
  double distance;
public:
    vector<Items> i1;
  Address add;
    // Constructors
    Sender();
    // Getter functions
    string getName() const;
    int getAge();
    int getCnic();
    int getContactNo();
    double getLuggagePrice();
    bool getStatus();

    // Setter functions
    void setName(string newName);
    void setAge(int newAge);
    void setStatus(bool Send);
    void setCnic(int newCnic);
    void setContactNo(int newContactNo);
    void setLuggagePrice(double newLuggagePrice);

    // Other functions
    void senderAddress();
void PutInfo();
nlohmann:: json makeRecord();
void  find(  nlohmann::json& courier);
double  toRadians(double degrees);
double calculateDistance();
void  packageInfo(  nlohmann::json& senderInfo);



};


#endif //INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_SENDER_H
