#!/bin/bash

name="patrick"
export age=25

echo "Hello, world!, $name"
echo "date : "`date`

text="hello, world!"
echo ${text:0:5}
echo ${text:7}

text="I like seokjun"
echo ${text/seokjun/haejun}

text="I like cats, I really love cats"
echo ${text//cats/dogs}
echo ${#text}

# 중요 환경변수 설정도 변경 가능 unset env 초기화//cats/dogs
# unset 환경변수

# read
echo "이름을 입력하시오: "
read name
read -s -p "비밀번호를 입력하세요: " passward
echo "입력한 이름: $name"
echo "패스워드: $passward"
export namae=$name
./envTest

# 화면 출력 echo, printf
echo -n "이어지는 " # 개행없음
echo "문장"

echo -e "엔터가 들어가는\n 문장" # \n이 작동하게 하기위해서 -e를 사용
printf "이름: %s, 나이: %d\n" "홍길동" 25

# 중요!! argument 받기 $1 $2
echo "첫 번째 인자: $1" # source 파일 뒤에 붙이는 것에 대하여 인자로 인식
echo "두 번째 인자: $2"
echo "인자들의 갯수: $#"
echo "모든인자: $@"

#제어문 if
read -p "나이를 넣으시오: " age
if [ $age -lt 18 ]; then
    echo "성인이 아닙니다."
elif [ $age -gt 70 ]; then
    echo "노인입니다."
else
    echo "성인입니다."
fi

# 연산자 숫자편
# 같다 == : eq
# 같지않다 != : ne
# 크다 > : gt (greater then)
# 작다 < : lt (less then)
# 크거나 같다. >= : ge (greater then equal)
# 작거나 같다. <= : le (less then equal)

# 연산자 문자편
# 같다 == : = #! 헷갈리지 않게 주의!
# 같지않다 != : !=
# 길이가 0 len(문자열) : z
# 길이가 0 이 아님 len(문자열) : n
# 크거나 같다. >= : ge (greater then equal)
# 작거나 같다. <= : le (less then equal)