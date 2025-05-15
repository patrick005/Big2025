class Singleton:
    _instance = None # class variable

    def __new__(cls, *args, **kwargs):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
        return cls._instance
    def __init__(self, a):
        try:
            print(f"기본 a가 가지고 있는 값 {self.a}")
        except:
            pass
        self.a = a
        print(f"변견된 값 {self.a}")


def main():
    a = Singleton(10)
    b = Singleton(20)
    print(id(a), id(b))
    print(a == b)


if __name__ == "__main__":
    main()