//
// Created by lenovo on 4/7/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_RECIEVER_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_RECIEVER_H
#include<iostream>
using namespace std;
#include <vector>
#include"Person.h"
#include "Address.h"
#include <fstream>
#include "json.hpp"
class Receiver: public Person{
  bool receive;
public:

    Receiver();
    Address add;
    bool getReceive();

    void setReceive(bool Receive);

    void setName(string newName);

    void setAge(int newAge);
void PutInfo( );

nlohmann:: json makeRecord();
    

    void setCnic(int newCnic);

    void setContactNo(int newContactNo);

    string getName() const;

    int getAge();

    int getCnic();

    int getContactNo();

    void receiverAddress();

};


#endif //INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_RECIEVER_H
