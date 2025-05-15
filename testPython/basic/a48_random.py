import random

def main():
    for _ in range(10):
        print("random()", random.random()) # 0~1 사이 float
        print("uniform(10, 20) : ", random.uniform(10, 20)) # 두수 사이 소수
        print("randint()", random.randint(4, 15)) # 두 수 사이 정수
        print("range(200)", random.randrange(200)) # 넣은 수 이전까지의 랜덤
        print("choice", random.choice([1, 2, 3, 4, 5])) # type : ignore
        print("choices", random.choices([1, 2, 3, 4, 5], k = 5))
        li = [1, 2, 3, 4, 5]
        random.shuffle(li)
        print("shuffle: ", li)
        print("sample: ", random.sample([1, 2, 3, 4, 5], k = 5))


if __name__ == "__main__":
    main()