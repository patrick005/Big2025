# a10_input.py
def main():
    input_var = input("숫자를 입력하시오 : ")
    print(type(input_var), input_var)
    # print("input_var + 100 = ", input_var + 100)  # 에러 발생 -> input_var는 str 타입
    if input_var.isdigit(): # 숫자만 입력했는지 체크
        print("input_var + 100 = ", int(input_var) + 100)
    else:
        print(input_var, "는 숫자가 아닙니다.", sep="")

# indentation 주의
# c언어는 중괄호 기준 블록단위지만 python에서는 : 기준으로 들여쓰기를 통해 블록을 구분한다
# string 정의 "string.. 안녕하세요" + 'string.. 안녕하세요' <- 싱글쿼트와 더블쿼트는 동일하게 사용 가능 / 이건 취향차이
if __name__ == "__main__":
    main()