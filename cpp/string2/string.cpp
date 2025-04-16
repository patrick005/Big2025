#include <cstring>
#include <cassert>
#include "string.h"

std::ostream& operator<<(std::ostream& out , String& rhs)
{
    return out << rhs.str_;
}

String::String()
{
    str_ = new char[1];
    assert(str_);
    str_[0] = '\0';
    len_ = 0;
}

String::String(const char *s)
: str_(new char[strlen(s) + 1]) , len_(strlen(s))
{
    // str_ = new char[strlen(s) + 1];
    assert(str_);
    strcpy(str_ , s);

    // len_ = strlen(s);
}

String::~String()
{
    delete [] str_;
}

String::String(const String& rhs)
: str_(new char[rhs.len_ + 1]) , len_(rhs.len_) //생성자 초기화 리스트 3경우중 콜론 사용( 굳이 안해도 되지만 이러한 표기가 가능하다는 것을 보여주기 위해 사용해봄)
{
    // str_ new char[rhs.len_ + 1];
    assert(str_);
    strcpy(str_ , rhs.str_);

    // len_ = rhs.len_;
}

String& String::operator=(const String& rhs)
{
    if (this != &rhs){ 
        
        delete [] str_;
        str_ = new char[rhs.len_ + 1];
        assert(str_);
        strcpy(str_ , rhs.str_);
    
        len_ = rhs.len_;
    }

    return *this;
}

bool String::operator==(const String& rhs) const
{
    return strcmp(str_ , rhs.str_) == 0;
}

const String String::operator+(const String& rhs) const
{
    char buf[strlen(str_) + strlen(rhs.str_) + 1];
    strcpy(buf , str_);
    strcat(buf , rhs.str_);

    String result(buf);
    return result;
}

const char *String::c_str() const
{
    return str_;
}

int String::size() const
{
    return len_;
}