# a44_iteration.py
from collections.abc import Iterable

class SimpleIter:
    def __init__(self, start, end):
        self.current = start
        self.end = end
        
    def __iter__(self):
        return self
    
    def __next__(self):
        if self.current >= self.end:
            raise StopIteration
        value = self.current
        self.current += 1
        return value
    
def main():
    iter_a = SimpleIter(1, 10)

    for i in iter_a:
        print(i)
    li = list()
    dict_a = dict()
    if isinstance(li, Iterable):
        print("li is iterable")
    if isinstance(dict_a, Iterable):
        print("dict_a is iterable")
    if isinstance(iter_a, Iterable): # simpleiter 에서 정의를 안하고 두 메소드만 정의해도 상속된것처럼 출력된다
        print("iter_a is iterable")

if __name__ == "__main__":
    main()