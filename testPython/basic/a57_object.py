from collections.abc import Iterable
import random

class TestClass: # == class TestClass(object):
    pass


def main():
    t1 = TestClass()
    if isinstance(t1, TestClass):
        print("t1은 TestClass의 객체이다")
    if isinstance(1, TestClass):
        print("int(1)은 TestClass의 객체이다")
    else:
        print("int(1)은 TestClass의 객체가 아니다")

    if issubclass(int, TestClass):
        print("int는 TestClass를 상속받았다")
    else:
        print("int는 TestClass를 상속받지 않았다")
        
    if issubclass(list, Iterable):
        print("list는 iterable를 상속받았다")
    else:
        print("list는 iterable를 상속받지 않았다")

    if issubclass(TestClass, object):
        print("TestClass는 object를 상속받았다")
    else:
        print("TestClass는 object를 상속받지 않았다")

    print(
        issubclass(int, object),
        issubclass(float, object),
        issubclass(list, object),
        issubclass(dict, object),
        issubclass(tuple, object),
        issubclass(str, object),
        issubclass(random.Random, object)
        )

if __name__ == "__main__":
    main()