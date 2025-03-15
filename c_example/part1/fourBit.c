//fourBit.c
// 볼드, 이탈릭, 쉐도우, 언더라인 을 표현하는 변수를 만들어라
// 비트연산
//볼드는 1번째자리 비트     0b00000001
//이탈릭은 2번째자리 비트   0b00000010
//쉐도우는 3번째자리 비트   0b00000100
//언더라인은 4번째자리 비트 0b00001000
//볼드이면서 언더라인이면   0b00001001

#include <stdio.h>

int main(void)
{
    // int bold = 0;
    // int italic = 0;
    // int shadow = 0;
    // int underline = 0;

    unsigned char attr; // 8bit 8개의 속성
    //char attr; //char로 할 때, 음수가 들어가기에 반드시 unsigned를 써야한다
    
    attr = attr ^ attr; // 모두 0으로 설정
    
    attr = attr | 0b00000001; // attr 볼드로 설정 
    //-> 0000에 0001 or연산으로 추가
    printf("attr: 0x%02x\n", attr);
    //0x01 -> 0001 : 볼드

    attr = attr | (0b00000010 + 0b00000100); // attr 이탈릭 쉐도우 추가
    //-> 0001로 위에서 지정된 것에 
    // 0010, 0100을 합산한 연산에 대해 or연산으로 추가
    printf("attr: 0x%02x\n", attr);
    //0x07 -> 0111 : 쉐도우 이탈릭 볼드

    attr = attr & (~0b00000001); // 볼드제거
    //-> 0111로 위에서 지정된 것에
    // 0001을 not으로 뒤집어 1110 이 되며,
    // 0111 과 1110의 and 연산으로 같은거만 1을 남겨서 0110
    printf("attr: 0x%02x\n", attr);
    //0x06 -> 0110 -> 이탈릭 쉐도우


    return 0;
}