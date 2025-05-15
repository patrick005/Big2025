# a09_operator.py
def main():
    pi = 3.141592
    # type casting
    int_pi = int(pi)
    print(type(int_pi), int_pi)
    str_pi = str(pi)
    print(type(str_pi), str_pi)
    # pi = 'three'
    # int_pi = int(pi) # 에러 발생

    print("pi + 2 = ", pi + 2)
    print("pi - 2 = ", pi - 2)
    print("pi * 2 = ", pi * 2)
    print("pi / 2 = ", pi / 2)
    print("pi // 2 = ", pi // 2)
    print("pi % 2 = ", pi % 2)
    print("pi ** 2 = ", pi ** 2)

if __name__ == "__main__":
    main()