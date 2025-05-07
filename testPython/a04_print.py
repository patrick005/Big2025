# a04_print.py

def main():
    print(1234567)  # C 에서는 '\n'을 붙여야 줄바꿈이 된다
    print(1_234_567) # python 에서는 '_'를 통해 숫자를 구분할 수 있다 / C에서는 '를 통해 숫자를 구분한다
    print("patrick")
    print(3.141592)
# python에서는 *를 통해 unpacking을 지원한다
    print("this is ", "python", "class")
    print(10, 20, 30, "hi", "fifty")
    print() # 줄바꿈
    print("this is ", "python", "class", sep="*", end="")
    print("this is ", "python", "class", sep="-")

if __name__ == "__main__":
    main()