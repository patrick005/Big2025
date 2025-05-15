import enum


def main():
    print(a:=range(10)) # := 코끼리문. 대입과 동시에값을 사용
    print(a.count(2))
    print(a.step)
    print(a.index(1))
    print(list(a))

    for i in range(10):
        print(f"{i+1} 번째 출력입니다.")

    list_a = ["choi", 123, 3.3]

    for i, ele in enumerate(list_a):
        print(f"{i}번째 원소의 값은 {ele} 입니다.")

    num = [0, 1, 2]

    for ele, i in zip(list_a, num):
        print(f"{i}번째 원소의 값은 {ele} 입니다.")



if __name__ == "__main__":
    main()