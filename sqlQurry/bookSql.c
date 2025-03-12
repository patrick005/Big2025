#include <mysql.h>
#include <stdio.h>
#include <string.h>

//sudo apt install libmysql++*
//mysql사용을 위한 설치
//dpkg -L libmysqlclient-dev | grep mysql.h
//위치확인
//.vscode/c_cpp_properties.json에서 Path 설정

int main(void){

    return 0;
}
//외부라이브러리라 3가지를 명시해야한다
//cc -o bookSql bookSql.c -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient
//-I-L-l

//libmysqlclient.so libmysqlclient.a

