# a17_list.py
import datetime

def main():

    # 크기 제한 없다.
    # 모든 다른 타입의 객체가 동시에 들어갈 수 있다.
    # iterable 하다. ...

    # 선언
    list_a = list()
    list_b = [1, 2, [3, 4, 5]]
    print(type(list_a), type(list_b))

    ptime = datetime. datetime.now()
    list_c = [1,2, 3.14, "patrick", ptime]

    # print(list_c[3]. list_c[4])
    print(list_b[1:])
    print(list_b[2][1], list_b[2][2])

    
    list_a = list_b
    print(list_a)

if __name__ == "__main__":
    main()