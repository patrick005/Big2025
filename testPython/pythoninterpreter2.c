//pythoninterpreter2.c
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
    char arg[256];
} Instruction;

// 파서
Instruction parse(const char* source){
    Instruction inst;
    inst.opcode = OP_UNKNOWN; // 초기화
    inst.arg[0] = '\0'; // 초기화

    const char *prefix = "print(\"";
    size_t prefix_len = strlen(prefix);

    if(strncmp(source, prefix, prefix_len) == 0){
        const char *end_quote = strchr(source + prefix_len, '"');
        const char *end_paren = strchr(end_quote ? end_quote + 1 : NULL, ')');

        if(end_quote && end_paren){
            size_t len = end_quote - (source + prefix_len);
            if(len < sizeof(inst.arg)){
                strncpy(inst.arg, source + prefix_len, len);
                
                inst.arg[len] = '\0';
                inst.opcode = OP_PRINT;
            }
            
        }
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

    printf("파이썬 프로토 타입 V1.0 (print(\"hello\")): ");
    while(1){
        printf("\n>>>");
        fgets(source, sizeof(source), stdin);
        source[strcspn(source, "\n")] = 0; // 개행 문자 제거
        if(strcmp(source, "exit") == 0){
            break;
        }

        Instruction inst = parse(source);
        excute(inst);

    }
    return 0;
}


