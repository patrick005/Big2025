# a64_destructor.py

class Test:
    def __ini__(self, name):
        self.name = name
        print(f"{self.name} - 생성되었습니다.")

    def __del__(self):
        print(f"{self.name} - 파괴되었습니다.")

def main():
    a = Test("A")
    b = Test("B")
    c = Test("C")
    print(a,b,c)
    del c


if __name__ == "__main__":
    main()