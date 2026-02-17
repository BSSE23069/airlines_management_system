//
// Created by lenovo on 4/7/2024.
//

#include "Person.h"
Person::Person(){
  name="";
  age=0;
  cnic=0;
  contactNo=0;
}
Person::Person(string name,int age,int cnic,int contactNo){
  this->name=name;
  this->age=age;
  this->cnic=cnic;
  this->contactNo=contactNo;
}