# Big2025
고려대 HRD 빅데이터 교육과정을 정리한 저장소입니다.

## 고려대 HRD 빅데이터 교육과정 담당자
담당자명: 김민성 책임연구원  
연락처 : 044-860-3836  
   <tab>010-4321-5754  </tab>
이메일 : ksonic@korea.ac.kr  

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
 
 ---
  
1. VMware Workstation Pro 설치(카톡으로 배포)
- 가상환경 안에서 os(운영체제)로 리눅스를 설치하여 실습
범용 리눅스인 우분투
2. ubuntu 22.04 LTS Desktop image download

3. VMware Player에서 새로운 가상 환경 생성
 1) VMware Player을 실행하여 ubuntu 설치한 것을 선택
 2) 프로젝트 생성하여 프로젝트명 작성 및 아이디 비번 만들기(aa)
  - 비번은 자주 사용하니, 중요 프로젝트가 아니라면 간단히
  - 세부설정: 하드 50~100GB / 가상 램은 4~8GB / Processors core 6
   (코어는 높으면 경고 문구를 띄워주니 안 뜰 때까지 낮추기)
  3) 디폴트값 따라가며 키보드는 나중에 변경하니 아무거나, 시간설정은 서울로 하면 됨
  4) 설정에서 한글로 바꿀 때 파일명에 대해서도 한글로 바꾸는 것은 적용하지 않기
  5) cmd를 여는 방법: ctrl + alt + t 

---

infinit.c
mkdir 폴더명 -> 폴더명 디렉터리 생성
cd 폴더명 -> 을 통한 폴더명으로 이동
tab -> 을 통한 자동완성 기능이 있음
touch 파일명 -> touch를 통한 빈 파일을 생성
ls -> 해당 디렉토리에 내용물 리스트 불러오기
nano 파일명 -> 해당 파일 편집 (nano에서는 tab으로 들여쓰기 안 됨, 차라리 4번 띄우기)
ctrl s -> 저장
ctrl x -> 나가기
cat 파일명 -> 내용물 보기
cc 파일명 -> 해당 파일 적용/컴파일
./ -> 실행?
./a.out -> 컴파일 된 해당 파일 실행
ps -> 프로세스가 실행중인지 알아볼 때
ctrl c -> 프로세스 중단
sudo apt install 패키지명 -> sudo(관리자권한 or 강제로) 패키지를 설치




===
# 2일차 수업

- include#include A
#include B
에 대해 A와 B를 불러오는 것이다.
만약 A파일 안에 #include B가 있는 상태로 위와 같이 사용한다면
A와 B를 불러오는데, A안에 B를 한번 더 불러오기에 A, B, B를 불러오는 것 이기에
이러한 부분에서 include의 사용에 주의해야한다

- main 함수의 형태
int /main/()/{ return 0;}
리턴값의 타입 / 식별자(함수명) / (나중에 설명해줌) / { ~~~return (맨앞의 선언에 해당하는 데이터);}
선언의 예)
int -> 숫자
void -> 공란
char -> 문자

- Type
--    -정수형	
      ㄴ 문자형 char()
      ㄴ void	-  함수 출력을 하지 않을 때
		  ㄴ 함수 입력을 안 받을 때
		  ㄴ 임의의 인자를 전달*
임의의 인자: type 미정이라 뭘 줄진 몰라도 뭔갈 줄 것이기에 미리 선언이라도 한다는 느낌?


%f(실수형)이나 %lf에 대해 중간에 .(숫자)의 형태로 자리수를 지정해줄 수 있다
ex) %.2f -> 소수점 2번째 자리까지 출력
ex) %.3f -> 소수점 3번째 자리까지 출력



4. 연산자(계산)
폰 노이만 머신  -- 폰 노이만 구조 (바이트머신 : 1바이트 단위로 처리)
		ㄴ 하버드 구조

┏code		      ┓	      ┏ cpu ┓
┗information	┛  ->   ┗     ┛     세트로 cpu에 들어가서 처리되면 폰 노이만 구조
                      
	[code]             ┏ cpu ┓
 [information]  ->   ┗     ┛  		각 개별로 cpu에 들어가서 처리되면 하버드 구조

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
연산자
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


printf("%d %d %d\n", 100, 0144, 0x64);
진수 관련 출력 방법 :
0x 로 붙으면 16진법
0o로 붙으면 8진법 옥타로 묶어라
0b로 붙으면 2진법 바이너리로 묶어라

printf("%lldLL\n", 10000000000LL);
안과 밖에 LL을 써줌으로써 LongLong 형태라고 명시해준 것 

printf("%f %f\n", 2.718, 3.141592F);
f 실수형으로 표현을 한다고 뒤에 F로 명시해준 것

printf("%d %d %d\n", 'A', 'a', '0');
뒤에 A a 0을 숫자형으로 바꾸면 아스키 코드값

printf("%c %c %c\n", 65, 97, 48);
뒤에 숫자를 글자형으로 바꾸면 아스키 코드 값에 의해 A a 0


