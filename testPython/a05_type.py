# a05_type.py
def main():
    abc = str() # str class 클래스로 객체 선언! 정식 선언
    abc2 = "hi" # str class 파이썬의 약식 선언
    print(type(abc))
    print(type(abc2)) # 파이썬에서 빌드인 class 에 대해서는 소문자로 시작
    abc = 4
    print(type(abc))
    abc = 3.14
    print(type(abc))
    abc = [1, 2, "three"] # STL의 벡터와 비슷한 개념, stl 개념 포괄한 list -> stl은 뭐든 받지만 한종류만, list는 여러종류
    print(type(abc))

if __name__ == "__main__":
    main()