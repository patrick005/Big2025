#ifndef EMPTY_H
#define EMPTY_H

class Empty{
public:
    // Empty(){ } //in-line함수로 만든다고 알면됨 나중에 설명해줌
    // Empty(const Empty& rhs){ /* memberwise copy*/ } //복사 생성자
    // ~Empty(){ } //cpp 안 만들고 이렇게 써도 된다를 보여주려고 작성

    // Empty& operator=(const Empty& rhs){ /* memberwise copy*/ return *this; } //복사 치환 연산자
    
    // Empty* operator&(){ return this; }
    // const Empty* operator&() const{ return this; } // 함수 중복을 인자의 타입, 인자의 개수, const 유무로 다르면 사용 가능

    // 이동 생성자
    // 이동 대입 연산자
};




#endif