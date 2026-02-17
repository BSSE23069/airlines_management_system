//
// Created by lenovo on 4/7/2024.
//

#ifndef INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_PERSON_H
#define INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_PERSON_H
#include<iostream>
using namespace std;
#include <vector>

//#include "../Accounts/Account.h"

class Person {
public:
  string name;
  int age;
  int cnic;
  int contactNo;
  Person();
  Person(string name,int age,int cnic,int contactNo);
    virtual void PutInfo()=0;
};


#endif //INC_2024_SPRING_SE102TB_PROJECT_SE102B_E_PERSON_H
