# a06_frame.py
import sys

frame = sys._getframe() # root frame
abc = int()
abc2 = list()

print("현재 프레임: ",frame)  # 현재 함수 이름
print("코드 객체: ", frame.f_code)
print("로컬 변수: ", frame.f_locals)
# __file__ : 현재 파일의 이름
# __package__ : 현재 파일의 패키지 이름
# __ doc__ : 현재 파일의 docstring
# __spec__ : 현재 파일의 spec
# ...
print("module_frame co name : ", frame.f_code.co_name)

def main():
    a = 123
    b = [3, 4, 5]
    main_frame = sys._getframe() # main frame
    print("main_frame co name : ", main_frame.f_code.co_name)
    print("local 변수 : ", main_frame.f_locals)
    print("전역 변수 : ", main_frame.f_globals)

if __name__ == "__main__":
    main()