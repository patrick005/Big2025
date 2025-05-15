# student 58번의 학생 총점 평균 이 실행할 때마다 랜덤입니다
# -> 고정적인 데이터로 100명의 학생을 처리하는 프로그램을 만드세요.
# 1. 데이터 생성 후 저장하는 프로그램 100명
# 2. studnets.txt를 읽어서 클래스를 생성하고 처리하는 프로그램

import random
import os

def create_student(name, korean, math, english, science):
    return {
        "name": name,
        "korean": korean,
        "math": math,
        "english": english,
        "science": science,
    }

def student_get_sum(student):
    return student["korean"] + student["math"] + student["english"] + student["science"]

def student_get_average(student, num):
    return student_get_sum(student) / num

def student_to_string(student, num):
    return f'{student["name"]}\t{student_get_sum(student)}\t{student_get_average(student, num):.2f}'

def generate_and_save_students(filename="students.txt", num_students=100):
    hanguls = list("최강박이손정적고구류오김송곽유")
    hanguls2 = list("가나다라마바사아자차카파타하길진재형준석화섭윤진")
    students_data = []
    for _ in range(num_students):
        student = create_student(
            random.choice(hanguls) + "".join(random.choices(hanguls2, k=2)),
            random.randint(65, 100),
            random.randint(65, 100),
            random.randint(65, 100),
            random.randint(65, 100),
        )
        students_data.append(student)

    with open(filename, "w", encoding="utf-8") as file:
        for student in students_data:
            file.write(f'{student["name"]}\t{student["korean"]}\t{student["math"]}\t{student["english"]}\t{student["science"]}\n')
    print(f"'{filename}' 파일에 {num_students}명의 학생 데이터가 저장되었습니다.")

def load_students(filename="students.txt"):
    students = []
    try:
        with open(filename, "r", encoding="utf-8") as file:
            for line in file:
                name, korean, math, english, science = line.strip().split("\t")
                student = create_student(name, int(korean), int(math), int(english), int(science))
                students.append(student)
        print(f"'{filename}' 파일에서 {len(students)}명의 학생 데이터를 로드했습니다.")
        return students
    except FileNotFoundError:
        print(f"'{filename}' 파일을 찾을 수 없습니다.")
        return None

def process_students(students):
    if students and len(students) > 57:
        student_58 = students[57]
        print(f"\n58번 학생 ({student_58['name']}) 총점 평균: {student_get_average(student_58, 4):.2f}")
    elif students:
        print("\n58번 학생 데이터를 찾을 수 없습니다.")
    else:
        print("\n처리할 학생 데이터가 없습니다.")

def main(filename="students.txt"):
    if os.path.exists(filename):
        print(f"'{filename}' 파일이 존재합니다. 데이터를 로드합니다.")
        students = load_students(filename)
        if students:
            process_students(students)
    else:
        print(f"'{filename}' 파일이 존재하지 않습니다. 데이터를 생성합니다.")
        generate_and_save_students(filename)
        students = load_students(filename)
        if students:
            process_students(students)

if __name__ == "__main__":
    main()