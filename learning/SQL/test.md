1일차-실습  
---
## 다른 유저가 가지고 있는 테이블 복사  

### EMP테이블 생성  
```spl  
CREATE TABLE EMP  
AS  
SELECT * FROM HR.EMP ;  
```  

### EMP 컬럼 설명  
|컬럼명|해석|
|:-----|:----|
|EMPLOYEE_ID|사번|
|FIRST_NAME|성|
|LAST_NAME|이름|
|EMAIL|이메일|
|PHONE_NUMBER|전화번호|
|HIRE_DATE|입사일|
|JOB_ID|직군|
|SALARY|월급, 급여|
|COMMISSION_PCT|수당율|
|MANAGER_ID|직속상관 사번|
|DEPARTMENT_ID|근무 부서번호|



## 기본 쿼리문
```sql
SELECT ~  
FROM  ~ ;  
[ WHERE ~  
GROUP BY ~  
HAVING ~  
ORDER BY	~	]  
```  

## SELECT 
- 컬럼명, 컬럼명, ... : 해당 컬럼 지정
- * : 모든 컬럼
- 수식
- 함수
- AS : 컬럼 별칭
- || : 결합연산자
- DISTINCT : 중복행 제거

### 예제

- 모든사원 모든 정보 확인
```sql
SELECT *
FROM EMP;
//모든사원 모든 정보+연봉 확인
SELECT EMP.*, SALARY*12 AS YEAR_SALARY
FROM EMP;
```
==\>\*(아스타) 외에 추가로 지정해서 출력을 하려면 [(테이블이름).*] 로 표기한다

- 이름, 월급 지정
```sql
SELECT LAST_NAME, SALARY
FROM EMP;
```  
- 이름, 월급, 연봉 지정
```sql
SELECT LAST_NAME, SALARY, SALARY * 12
FROM EMP;
```

- 이름, 월급, 연봉 지정에서 연봉 칼럼명 지정
```sql
SELECT LAST_NAME, SALARY, SALARY * 12 AS YEAR_SALARY
FROM EMP;
```
==\> AS 생략가능/실무에선 TABLE에서 오류 생기기때문에 생략함

- 칼럼 결합하여 표기
```sql
SELECT FIRST_NAME || ' ' || LAST_NAME
FROM EMP;
```

- AS로 주는 임시명에 공백이 있을 경우에 ""를 사용(공백 없이 한 단어를 사용할 때에도 "" 가능)
```sql
SELECT FIRST_NAME || ' ' || LAST_NAME AS "MY NAME"
FROM EMP;
```

- 부서명 출력
```sql
SELECT DEPARTMENT_ID
FROM EMP;
```
- 중복없이 부서명 출력
```sql
SELECT DISTINCT DEPARTMENT_ID
FROM EMP;
```

---


## 정렬

- ORDER BY 컬럼명 [옵션], 컬럼명 [옵션], 컬럼명 [옵션], ......

- 옵션
  -> 오름차순 : ASC , 기본이므로 보통 생략
  -> 내림차순 : DESC

---

- 이름, 월급을 월급 많은 순(역순)으로 정렬하고, 동렬에 대해 이름 순(정순)
```sql
SELECT LAST_NAME, SALARY
FROM EMP
ORDER BY SALARY DESC , LAST_NAME;
//스키마 구조로 요약시 추가
DESC EMP;
```

- INDEX 컬러명 대신으로 사용
SELECT LAST_NAME, SALARY
FROM EMP
ORDER BY 2 DESC , 1;

------------------------------------------------------------------------------------------------------------------------

# WHERE 절

- 조건에 맞는 행만 검색
- 조건식 => T, F => TRUE 인 행만 검색
- 좌항(컬럼명) 비교연산자 우항(수식)
- 비교연산자(관계연산자) : >, >=, <, <=, =, !=, <>  (<>은 오라클이 지원하는 !=)

//월급 15000 이상인 사람
SELECT LAST_NAME, SALARY
FROM EMP
WHERE SALARY >= 15000
ORDER BY 2 DESC , 1;

# 숫자 조건 검색
- 오직 숫자만 : 천단위콤마, 화폐단위, 표시형식

SELECT LAST_NAME, SALARY
FROM EMP
WHERE SALARY >= 15000;

# 문자 조건 검색
- 문자는 작은 따옴표로 감싼다
- 작은 따옴표 안의 문자의 대소문자는 구분함

//이름이 'Chen'인 사람
SELECT *
FROM EMP
WHERE LAST_NAME = 'Chen';

# 날짜 조건 검색
- 날짜도 작은 따옴표로 감싼다 : '2000-10-10'
- 날짜로 인식이 안 되는 경우 : TO_DATE('2000-10-10', 'YYYY-MM-DD')

//2005년 이전 입사사원의 이름과 입사일, 입사일 순 정렬 /  DESC 사용시 최근입사자순
SELECT LAST_NAME, HIRE_DATE
FROM EMP
WHERE HIRE_DATE < '2005-01-01'
ORDER BY 2;

//위 내용 인식이 안 될 시
SELECT LAST_NAME, HIRE_DATE
FROM EMP
WHERE HIRE_DATE < TO_DATE('2005', 'YYYY')
ORDER BY 2;

----------------------------------------------------------------------------------------------------------------

# 기타 비교연산자

- >, <, <=, >=, =, !=
- BETWEEN ~ AND, IN, LIKE, IS(오라클에서만)

# BETWEEN ~ AND
- 범위 검색
- BETWEEN 값1 AND 값2
- BETWEEN 최소값 AND 최댓값
- 값으로 숫자, 날짜, 문자(아스키 코드 값) 적용 가능

// BETWEEN 없이 10000~15000 받는 사람
SELECT LAST_NAME, SALARY
FROM EMP
WHERE SALARY >= 10000 AND SALARY <= 15000
ORDER BY 2 DESC;

//BETWEEN으로 교체
SELECT LAST_NAME, SALARY
FROM EMP
WHERE SALARY BETWEEN 10000 AND 15000
ORDER BY 2 DESC;

//2005년 입사사원의 이름과 입사일, 입사일 순 정렬 /  DESC 사용시 최근입사자순
SELECT LAST_NAME, HIRE_DATE
FROM EMP
WHERE HIRE_DATE BETWEEN '2005-01-01' AND '2005-12-31'
ORDER BY 2;

//2005년 입사에 입사한 인원이 아닌 사람
SELECT LAST_NAME, HIRE_DATE
FROM EMP
WHERE HIRE_DATE NOT BETWEEN '2005-01-01' AND '2005-12-31'
ORDER BY 2;

# IN
- 목록 안에 것을 검색

// IN연산자 없이 근무부서가 20, 30, 40
SELECT LAST_NAME, DEPARTMENT_ID
FROM EMP
WHERE DEPARTMENT_ID = 20
	OR DEPARTMENT_ID = 30
	OR DEPARTMENT_ID = 40;

// IN연산자로 근무부서가 20, 30, 40
SELECT LAST_NAME, DEPARTMENT_ID
FROM EMP
WHERE DEPARTMENT_ID IN (20, 30, 40);

# LIKE
- 패턴 검색
- 문자 컬럼에 사용

- % : 여러문자 대신
- _   : 한문자 대신

SELECT *
FROM EMP
WHERE LAST_NAME = 'Chen';

//C로 시작하는 모든 사람
SELECT *
FROM EMP
WHERE LAST_NAME LIKE 'C%';

//이름이 4글자인 사람
SELECT *
FROM EMP
WHERE LAST_NAME LIKE '____';

//이름의 2번째 문자가 a인 사람
SELECT *
FROM EMP
WHERE LAST_NAME LIKE '_a%';

# IS(Orakle 전용 연산자)
- NULL 을 비교할 때

//수당율이 미입력된 사람의 이름과 수당율
SELECT LAST_NAME, COMMISSION_PCT
FROM EMP
WHERE COMMISSION_PCT = NULL;
==>검색결과 없음!!
SELECT LAST_NAME, COMMISSION_PCT
FROM EMP
WHERE COMMISSION_PCT IS NULL;

//수당율이 미입력되지 않은 사람
SELECT LAST_NAME, COMMISSION_PCT
FROM EMP
WHERE COMMISSION_PCT IS NOT NULL;

#### IS는 뒤에 NOT / BETWEEN은 앞에  NOT 붙이면 부정형

~교제 119P


