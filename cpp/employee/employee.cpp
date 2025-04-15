//employee.cpp
#include "employee.h"

Employee::Employee(int id, String name, Employee *pManager){
    this->id = id;
    this->name = name;
    this->pManager = pManager;
}
/*
Employee::~Employee(){
    없어도 컴파일러가 잘 해줌
}
*/

int Employee::getId(){
    return this->id;
}
String Employee::getName(){
    return this->name;
}
Employee *Employee::getManager(){
    return this->pManager;
}

bool Employee::isManager(){
    return this->pManager == NULL;
}