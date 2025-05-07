# a07_locals_vars.py

b = [1, 2, 3, 'four']

def main():
    a = 123
    print("로컬 변수 : ", locals())
    print("vars 변수 : ", vars())
    print("전역 변수 : ", globals())

if __name__ == "__main__":
    main()