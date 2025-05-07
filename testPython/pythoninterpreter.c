//pythoninterpreter.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum{
    OP_PRINT,
    OP_UNKNOWN
} OpCode;

// 바이트 코드 -> .pyc
typedef struct{
    OpCode opcode;
    const char* arg;
} Instruction;

// 파서
Instruction parse(const char* source){
    Instruction inst;
    if(strncmp(source, "print(\"hello\")", 15) == 0){
        inst.opcode = OP_PRINT;
        inst.arg = "hello";
    }else{
        inst.opcode = OP_UNKNOWN;
        inst.arg = NULL;
    }
    return inst;
}

// PVM 가상 머신 실행기
void excute(Instruction inst){
    switch(inst.opcode){
        case OP_PRINT:
            printf("%s\n", inst.arg);
            break;
        case OP_UNKNOWN:
            printf("Unknown instruction\n");
            break;
    }
}

int main(){
    char source[256];

    printf("파이썬 프로토 타입 V1.0 (print(\"hello\")): \n>>>");
    fgets(source, sizeof(source), stdin);
    source[strcspn(source, "\n")] = 0; // 개행 문자 제거
    Instruction inst = parse(source);
    excute(inst);
    return 0;
}


