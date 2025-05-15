# a15_detetime.py
import datetime

# import test package

class Myclass:
    def __str__(self):
        return "test My class"

# 1. PATH PYTHONPATH에 있는 ~.py 파일들 대상 불러온다
# 2. package가 임포트
# 3. .so 파일을 임포트(dynamic loading) < c 모듈 만들기(cpython)
#     .(pyi(stub) .so)--> github.에서 c파일을 확인할 수 있음 -> 이것들 실행속도가 빠름
# GIL(Global Interpreter Lock) : PVM

def main():
    ptime = datetime.datetime.now()
    print(ptime) # __str__ 오버로딩이 되어서 나온다

    myclass = Myclass()
    print(myclass) 

    print(ptime.month)
    print(f"{ptime.year}년 {ptime.month}월 {ptime.day}일 ")

if __name__ == "__main__":
    main()