# example2.py
# 섭씨 -> 화씨 변환기 input -> casting -> 연산 -> 출력

def main():
    degree = input("섭씨를 정수로 입력하시오 : ")
    if degree.isdigit(): # 숫자만 입력했는지 체크
        # print("화씨로는 ", (float(degree) * 9 / 5) + 32, "F 입니다.") # (0°C × 9/5) + 32
        print(f"섭씨온도 {degree}도는 화씨온도 {(float(degree) * 9 / 5) + 32}F 입니다.")
    else:
        print(degree, "는 조건에 맞는 입력값이 아닙니다.", sep="")

if __name__ == "__main__":
    main()