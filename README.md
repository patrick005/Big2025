[![patrick's GitHub stats](https://github-readme-stats.vercel.app/api?username=aa)](https://github.com/aa/github-readme-stats)
[![patrick's GitHub stats](https://github-readme-stats.vercel.app/api?username=patrick005)](https://github.com/patrick005/github-readme-stats)


# Big2025
고려대 HRD 빅데이터 교육과정을 정리한 저장소입니다.

## 고려대 HRD 빅데이터 교육과정 담당자
담당자명: 김민성 책임연구원  
연락처 : 044-860-3836  
휴대폰 : 010-4321-5754  
이메일 : ksonic@<as>korea.ac.kr</as>  

## C언어
강사명: 최수길 강사님  
휴대폰: 010-4573-5540  
github: github.com/freshmea  
카톡ID: freshmea  

---

1일차
성취 – 무엇을 이룰 것인가
집중 – 무엇에 집중할 것인가

1. github를 잘 가꿔라 – 학습 정리
2. 포트폴리오(프로젝트) 준비 – github로 올리기
- 계획, 과정(자료수집, 작성, 디버깅), 결과
- 이런 육성 과정의 프로젝트는 주의 깊게 보지 않기 때문에, 개인 프로젝트를 진행하여야함
 ->거창하지 않더라도 작은거라도 해보자
- 정보를 찾고 만들어봤다라는 것만으로도 인식이 좋아짐
 -> 수동적이 아닌 능동적인 인상을 줄 수 있음
3. 알고리즘 연습
– 이력서에 소개하는 케이스도 있음(논리력 입증/과거엔 비중이 높았으나 현재 비중이 낮긴함)
- 이를 테스트 할 수 있는 사이트가 있음
1) 백준
2) 프로그래머스
3) 삼성 소프트웨어 ~ 

코딩보다는 프로젝트 전반을 이해하는 능력이 더 중요해져버림(코딩은 기본으로 깔고가는거지 무시가 아님)

운영체제 OS – windows, linux, mac
1. Linux
 1) Ubuntu
 2) Android
 3) Redhat
 4) CentOS
 5) Raspbian
 
 ===
# 2일차 수업

- include
```
#include A  
#include B
```
에 대해 A와 B를 불러오는 것이다.  
만약 A파일 안에 #include B가 있는 상태로 위와 같이 사용한다면  
A와 B를 불러오는데, A안에 B를 한번 더 불러오기에 A, B, B를 불러오는 것 이기에  
이러한 부분에서 include의 사용에 주의해야한다  

- main 함수의 형태
```
int /main/()/{ return 0;}
```
리턴값의 타입 / 식별자(함수명) / (나중에 설명해줌) / { ~~~return (맨앞의 선언에 해당하는 데이터);}  
선언의 예)  
int -> 숫자  
void -> 공란  
char -> 문자  
<p style="color:#FFFFFF;">0000</p>

### Type  
-정수형  
 * 문자형 char()  
 * void
   + 함수 출력을 하지 않을 때  
   + 함수 입력을 안 받을 때  
   + 임의의 인자를 전달*  
임의의 인자: type 미정이라 뭘 줄진 몰라도 뭔갈 줄 것이기에 미리 선언이라도 한다는 느낌?  


%f(실수형)이나 %lf에 대해 중간에 .(숫자)의 형태로 자리수를 지정해줄 수 있다  
ex) %.2f -> 소수점 2번째 자리까지 출력  
ex) %.3f -> 소수점 3번째 자리까지 출력  
  


4. 연산자(계산)  
폰 노이만 머신  -- 폰 노이만 구조 (바이트머신 : 1바이트 단위로 처리)  
		ㄴ 하버드 구조  
  
┏code	    ┓	    ┏ cpu ┓  
┗information┛  ->   ┗     ┛     세트로 cpu에 들어가서 처리되면 폰 노이만 구조  
  
	\[code]       ┏ cpu ┓  
 [information]  ->   ┗     ┛  	각 개별로 cpu에 들어가서 처리되면 하버드 구조  

컴퓨터의 구조 CS(computer science) - 대학 과정일 정도로 복잡하니 알아서 찾아봐라  
cpu / ram  / harddisk  
  
변수(variable): 변화가능한 수 ┏ a  
			    ┗ b  
			    ┗ var_a  
- 저장 가능한 메모리 공간에 확보 (식별화)  
		┗ 램 ┳ 메모리   
		       | 힙 : 아무 자리에나 malloc, calloc freo의 방식으로 저장  
			(자유롭다보니 메모리 리킹이 일어날 수 있음)  
		      ┗ 스택 : 주로 우리가 한 코딩: 바닥에서부터 쌓아올리는 방법  
		(함수 형태로 쌓아 올리다 보니 변수의 태가 변하면 치명적임)  
동적할당 변수 -> 힙 방식으로 램에서 처리하는 변수  

상수(constant): 코드가 변하지 않음  
0 1 2 3 4 5 6 7 8 9  -> 이런 숫자에 대해 이진법으로 설명하고 일일이 만들지 않도록함  
램의 메모리에 얹어버림  
```
#include <stdio.h>
int main(void){
    int a, b;
    printf("Input a, b : ");
    scanf("%d %d", &a, &b);

    printf("PLUS %d + %d = %d\n", a, b, a+b);
    printf("MINUS %d - %d = %d\n", a, b, a-b);
    printf("MULTIPLY %d * %d = %d\n", a, b, a*b);
    printf("DIVISION %d / %d = %d\n", a, b, a/b);
    printf("나머지 %d 나머지 %d = %d\n", a, b, a%b);
    return 0;
}
```

## 연산자
1) 산술연산자 : +, -, *, /, %  
2) 대입연산자: =  
3) 복합연산자: (1),2)의 결합) +=, -=, *=, =+  
4) 증감연산자: ++, --  
	- 전위: ++a -> 올려서 출력해라 
	- 후위: a-- -> 출력하고 올려서 저장해라  

전역변수: 프로그램 끝나도 살아남음  
- 자동으로 초기화가 되기 때문에 많이 사용했었음  
- 해킹의 단초라 사용을 안 하는 추세  
지역변수: 프로그램 끝나면 사라짐  
- 가비지값이 들어가 있을 수 있기에 초기화를 해주어야 함  

대입연산자가 증감연산자보다 우위임  

```
printf("%d %d %d\n", 100, 0144, 0x64);
```
진수 관련 출력 방법 :  
0x 로 붙으면 16진법  
0o로 붙으면 8진법 옥타로 묶어라  
0b로 붙으면 2진법 바이너리로 묶어라  

```
printf("%lldLL\n", 10000000000LL);
```
안과 밖에 LL을 써줌으로써 LongLong 형태라고 명시해준 것  

```
printf("%f %f\n", 2.718, 3.141592F);
```
f 실수형으로 표현을 한다고 뒤에 F로 명시해준 것  

```
printf("%d %d %d\n", 'A', 'a', '0');
```
뒤에 A a 0을 숫자형으로 바꾸면 아스키 코드값  

```
printf("%c %c %c\n", 65, 97, 48);
```
뒤에 숫자를 글자형으로 바꾸면 아스키 코드 값에 의해 A a 0  


