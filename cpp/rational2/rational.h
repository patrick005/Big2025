#ifndef RATIONAL_H
#define RATIONAL_H


class Rational{
private:                          //implemetation / 구현 세부 사항은 여기에 숨겨짐
    int num;                      //Numerator (분자) of the rational number
    int denom;                    // Denominator (분모) of the rational number


public: //interface / 객체와 상호 작용하기 위한 인터페이스
    Rational(int num, int denom); //constructor // 분자와 분모로 초기화하는 생성자
    Rational(int num);            // 분자만으로 초기화하는 생성자 (분모는 기본적으로 1)
    Rational();                   // 기본 생성자 (분자는 기본적으로 0, 분모는 기본적으로 1)
    ~Rational();                  // 소멸자 (이 경우 특정 정리 작업은 필요하지 않음)

    void operator=(const Rational& rr); 
    //const Rational&를 사용하는 이유는 원본 객체를 변경하지 않고 복사본을 만들기 위함
    // 오버로드된 대입 연산자. 'rr' Rational 객체의 값을 현재 Rational 객체에 할당합니다.
    // 'const Rational&'은 효율성(불필요한 복사 방지)과 소스 객체의 수정을 방지하기 위해 사용됩니다.

    bool operator==(const Rational& other)const;  // 오버로드된 동등 비교 연산자
    // 현재 Rational 객체를 다른 Rational 객체('other')와 동등한지 비교합니다.
    // 끝의 'const'는 이 메서드가 현재 객체의 상태를 수정하지 않음을 나타냅니다.
    // 두 유리수가 같으면 'true', 그렇지 않으면 'false'를 반환합니다.
    
    void normalize();   // 분자와 분모를 최대공약수(GCD)로 나누어 유리수를 가장 간단한 형태로 줄입니다.
                        // 또한 분모가 양수가 되도록 보장합니다.

    int getNum();     // 분자를 가져오는 메서드
    int getDenom();   // 분모를 가져오는 메서드

    void SetNum(int num);     // 분자를 수정하는 메서드
    void SetDenom(int denom); // 분모를 수정하는 메서드
};

#endif 
