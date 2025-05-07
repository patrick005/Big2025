# example1.py
# 파이썬으로 구구단 출력하기 9*9

def main():
    test = '{} * {} = {}'
    dan = '23456789'
    for i in dan:
        print(f"구구단 {i} 단")
        for j in dan:
            print(i, "*", j, "=", int(i) * int(j))
        print()

if __name__ == "__main__":
    main()