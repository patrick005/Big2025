/* string.o 다른사람꺼 긁어오면 안될수도 있음 컴파일 환경 자체 설정이 달라서인듯하니 직접 작업한걸로 하기
다른 사람이 생성한 .o 파일을 그대로 가져와 사용하는 것은 일반적으로 불가능하며, 반드시 해당 환경에서 코드를 다시 컴파일해야 합니다.
$ g++ -c main.cpp
$ g++ -c employee.cpp
$ g++ -o testEmployee main.o employee.o string.o
$ ./testEmployee 
*/

#include <iostream>
#include "employee.h"

void printEmployee(Employee *p){
    std::cout << "id: " << p->getId() << "  |name: " << p->getName() << " |manager: ";
    std::cout << ((p->isManager() ) ? "" : p->getManager()->getName()) << std::endl; //상급자가 없으면 공백, 있으면 상급자의 이름을 출력
}

int main(){
    // Employee e1(1, "Park Jung Seok", NULL);
    // Employee e2(2, "Sung Young Ho",   &e1);
    // Employee e3(3, "Choi Su Gil"    , &e1);
    // Employee e4(4, "Cho Min Sung",    &e1);
    // Employee e5(5, "Min Byung Hun",   &e4);
    // Employee e6 = e1;

    // e1 = e2; 

    // Employee employees[10]; // default 생성자를 불러오는데 정의를 안했으면 main.cpp: error: no matching function for call to ‘Employee::Employee()’ 라고 뜬다
    Employee *pEmployees[10];
    pEmployees[0] = new Employee (1, "Park Jung Seok",           NULL);
    pEmployees[1] = new Employee (2, "Sung Young Ho",   pEmployees[0]);
    pEmployees[2] = new Employee (3, "Choi Su Gil",     pEmployees[0]);
    pEmployees[3] = new Employee (4, "Cho Min Sung",    pEmployees[0]);
    pEmployees[4] = new Employee (5, "Min Byung Hun",   pEmployees[3]);

    for (int i = 0; i<5; ++i){
        printEmployee(pEmployees[i]);
    }

    for (int i = 0; i<5; ++i){
        delete pEmployees[i];
    }
    // std::cout << "id: " << e1.getId() << "  " << e1.getName() << std::endl;
    // std::cout << "id: " << e2.getId() << "  " << e2.getName() << std::endl;
    
    
    return 0;
}