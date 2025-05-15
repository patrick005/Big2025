# a42_generator3.py
def test():
    print("test A")
    yield 1
    print("test B")
    yield 2
    print("test C")
    yield 3

def main():
    print("main A")
    output = test()  # return object 만들고 실행은 따로

    print("main B")
    a= next(output)
    print(a)

    a= next(output)
    print(a)

    a= next(output)
    print(a)

#    a= next(output)
#    print(a) # StopIteration 발생

    try:
        a= next(output)
        print(a)
    except StopIteration as e:
        print("StopIteration Error")

    print("main C")

if __name__ == "__main__":
    main()