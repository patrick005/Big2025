// #include <stdio.h>

// int main() {
//     int number = 10;
//     int *ptr = &number; // number 변수의 주소를 포인터 ptr에 저장
    

//     printf("변수 number의 값: %d\n", number);
//     printf("변수 number의 주소: %p\n", &number);
//     printf("포인터 ptr이 가리키는 값: %d\n", *ptr);
//     printf("포인터 ptr의 주소: %p\n", &ptr);

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h> // malloc, free 함수를 사용하기 위해 필요

int main() {
    int *ptr;
    int size = 5;

    // malloc을 사용하여 동적으로 메모리 할당
    ptr = (int *)malloc(sizeof(int) * size);

    if (ptr == NULL) {
        printf("메모리 할당 실패\n");
        return 1; // 에러 발생 시 0이 아닌 값 반환
    }

    printf("동적으로 할당된 메모리의 시작 주소: %p\n", ptr);

    // 할당된 메모리에 값 저장 (예시)
    for (int i = 0; i < size; i++) {
        ptr[i] = i + 1;
    }

    printf("할당된 메모리의 값: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");

    // 포인터 ptr 자신의 주소 확인
    printf("포인터 ptr의 주소: %p\n", &ptr);

    // 더 이상 사용하지 않는 메모리는 반드시 해제해야 함
    free(ptr);
    ptr = NULL; // 해제 후에는 포인터를 NULL로 설정하는 것이 좋음

    return 0;
}