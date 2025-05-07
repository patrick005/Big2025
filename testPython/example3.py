# example3.py
# 문자열을 입력 받아서 단어를 카운트해서 결과를 출력하세요.

def main():
    f = open('testPython/data2.txt', 'r')
    data = f.read()
    # 입력 받은 문자열을 공백으로 나누어 리스트로 변환
    words = data.split()
    # 단어의 개수를 세기 위한 딕셔너리 생성
    word_count = {}
    # 각 단어를 순회하며 개수를 세기
    input_str = input("찾고자 하는 단어를 입력하시오 : ")
    for word in words:
        # 단어를 소문자로 변환하여 대소문자 구분 없이 카운트
        word = word.lower()
        input_str = input_str.lower()
        # 딕셔너리에 단어가 이미 존재하는지 확인
        if word in word_count:
            word_count[word] += 1
        else:
            word_count[word] = 1
    # 결과 출력
    if input_str in word_count:
        print(f"{input_str}의 개수는 {word_count[input_str]}입니다.")
    else:
        print(f"{input_str}는 존재하지 않습니다.")
    # 파일 닫기
    f.close()

if __name__ == "__main__":
    main()