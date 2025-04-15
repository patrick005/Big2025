//employee.h
#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "string.h"

class Employee{
private:
    int id;                 //사번
    String name;            //이름
    Employee * pManager;    //상급자 링크
    //is not generated list
    Employee(const Employee& rhs);
    Employee& operator=(const Employee& rhs);
public:
    Employee(int id, String name, Employee *pManager);
    // ~Employee(){ } 

    
    // Employee(){ } is not generated!
    // Employee(const Employee& rhs){ /* memberwise copy*/ } is not generated
    // Employee& operator=(const Employee& rhs){ /* memberwise copy*/ return *this; } 
    
    // Employee* operator&(){ return this; }
    // const Employee* operator&() const{ return this; }

    int getId();
    String getName();
    Employee *getManager();

    bool isManager();

};




#endif