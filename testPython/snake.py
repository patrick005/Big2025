import pygame
import time
import random
import datetime

# 게임 초기화
pygame.init()  # Pygame 모듈을 초기화하여 게임에 필요한 모든 시스템을 설정

# 색상 정의 (RGB 값)
white = (255, 255, 255)
yellow = (255, 255, 102)
black = (0, 0, 0)
red = (213, 50, 80)
green = (0, 255, 0)
blue = (50, 153, 213)

# 게임 화면 크기 설정
width = 600  # 게임 화면 너비 (가로 길이)
height = 400  # 게임 화면 높이 (세로 길이)
dis = pygame.display.set_mode((width, height))  # Pygame 화면을 설정, 주어진 크기로 디스플레이 창을 생성
pygame.display.set_caption('Snake Game')  # 게임 창의 제목을 'Snake Game'으로 설정

# 블록 생성 영역 크기와 위치 설정 (먹이와 뱀이 생성될 수 있는 영역 설정)
block_area_top = 100  # 상단에 점수 영역을 위해 100 픽셀만큼 여백을 둠
block_area_left = 50  # 좌우 여백을 50 픽셀로 설정
block_area_right = width - block_area_left  # 오른쪽 끝점 계산 (화면 너비에서 좌우 여백을 제외)
block_area_bottom = height - block_area_top  # 블록 생성 영역의 하단 끝점 (화면 높이에서 상단 여백을 제외)

# 게임 속도와 블록 크기 설정
clock = pygame.time.Clock()  # 게임 속도 관리를 위한 Clock 객체 생성
snake_block = 10  # 뱀의 한 블록 크기를 10픽셀로 설정
snake_speed = 5  # 게임 시작 시의 기본 속도 설정

# 폰트 정의 (텍스트를 화면에 출력할 때 사용할 폰트)
font_style = pygame.font.SysFont("bahnschrift", 25)  # 메시지와 점수를 출력할 때 사용할 기본 폰트 설정
score_font = pygame.font.SysFont("comicsansms", 35)  # 점수를 출력할 폰트 설정

# 최고 점수를 저장할 변수 (게임이 진행되는 동안 최고 점수를 기록함)
highest_score = 0  # 게임이 시작되면 최고 점수를 0으로 초기화

# 현재 점수를 화면에 출력하는 함수
def Your_score(score):
    value = score_font.render("Your Score: " + str(score), True, white)  # 점수를 문자열로 변환하여 흰색으로 렌더링
    dis.blit(value, [0, 0])  # 화면의 좌측 상단 (x=0, y=0) 위치에 점수 출력

# 최고 점수를 화면에 출력하는 함수
def display_highest_score():
    value = score_font.render("Highest Score: " + str(highest_score), True, yellow)  # 최고 점수를 노란색으로 렌더링
    dis.blit(value, [0, 30])  # 현재 최고 점수를 좌측 상단에서 약간 아래 (y=30) 위치에 출력

# 뱀의 각 블록을 화면에 그리는 함수
def our_snake(snake_block, snake_list):
    for x in snake_list:  # 뱀의 각 블록에 대해
        pygame.draw.rect(dis, green, [x[0], x[1], snake_block, snake_block])  # 뱀 블록을 그린다 (초록색으로)

# 메시지를 화면에 출력하는 함수
def message(msg, color):
    mesg = font_style.render(msg, True, color)  # 주어진 색상으로 메시지를 렌더링
    dis.blit(mesg, [width / 6, height / 3])  # 메시지를 화면의 중앙에 출력 (가로는 화면의 1/6, 세로는 화면의 1/3 위치)

# 먹이가 화면 테두리에 너무 가깝게 생성되지 않도록 안전한 범위 내에서 먹이를 생성하는 함수
def generate_food():
    safe_margin = 20  # 테두리로부터 떨어질 최소 거리 설정 (20 픽셀)
    
    # X축과 Y축에서 테두리로부터 safe_margin 이상 떨어진 범위에서 먹이의 좌표를 랜덤으로 생성
    food_x = round(random.randrange(block_area_left + safe_margin, block_area_right - safe_margin) / 10.0) * 10.0
    food_y = round(random.randrange(block_area_top + safe_margin, block_area_bottom - safe_margin) / 10.0) * 10.0
    return food_x, food_y  # 먹이의 좌표 반환

# 게임 종료 후 처리 함수 (최고 점수 갱신 및 3초 대기)
def game_over_sequence(score):
    global highest_score  # 전역 변수로 선언된 최고 점수를 사용
    if score > highest_score:  # 현재 점수가 최고 점수보다 크면
        highest_score = score  # 최고 점수를 현재 점수로 갱신
    time.sleep(3)  # 3초 대기 (게임이 재시작되기 전에 잠시 기다림)

# 게임 루프 함수 (게임이 진행되는 동안 이 함수가 계속 호출됨)
def gameLoop():
    global highest_score  # 전역 변수로 선언된 최고 점수를 사용
    start_time = datetime.datetime.now()  # 게임 시작 시간 기록 (사용하지 않지만 추후 기능 확장에 활용 가능)

    game_over = False  # 게임이 종료되었는지 여부 (False로 초기화)
    game_close = False  # 뱀이 충돌했는지 여부 (False로 초기화)

    # 뱀의 초기 위치 설정 (화면 중앙)
    x1 = width / 2
    y1 = (block_area_top + block_area_bottom) / 2  # 상단 여백을 고려한 중앙 좌표

    x1_change = 0  # 뱀의 x축 이동 변화 (처음에는 움직이지 않음)
    y1_change = 0  # 뱀의 y축 이동 변화 (처음에는 움직이지 않음)

    snake_list = []  # 뱀의 각 블록 위치를 저장하는 리스트
    length_of_snake = 1  # 뱀의 초기 길이는 1

    # 가장자리 규칙 적용한 먹이 생성 (먹이의 x, y 좌표를 생성)
    foodx, foody = generate_food()

    current_speed = snake_speed  # 게임 시작 속도 설정
    score = 0  # 점수 초기화

    last_difficulty_increase_time = time.time()  # 난이도 상승 시간을 기록 (10초마다 난이도 상승)

    # 게임이 종료되지 않은 동안 계속 루프
    while not game_over:

        # 뱀이 충돌하여 게임이 종료된 경우
        while game_close == True:
            dis.fill(blue)  # 배경을 파란색으로 채움
            message("You Lost! Press Enter to Restart", red)  # 게임 종료 메시지를 출력
            Your_score(score)  # 현재 점수를 화면에 출력
            display_highest_score()  # 최고 점수를 화면에 출력
            pygame.display.update()  # 화면 업데이트

            for event in pygame.event.get():  # 키 입력 이벤트 처리
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_RETURN:  # Enter 키를 누르면
                        game_over_sequence(score)  # 게임 종료 처리
                        gameLoop()  # 게임 재시작

        # 키보드 입력을 통해 뱀의 방향을 설정
        for event in pygame.event.get():
            if event.type == pygame.QUIT:  # 게임 창을 닫으면 게임 종료
                game_over = True
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:  # 왼쪽 화살표 키 입력 시 왼쪽으로 이동
                    x1_change = -snake_block
                    y1_change = 0
                elif event.key == pygame.K_RIGHT:  # 오른쪽 화살표 키 입력 시 오른쪽으로 이동
                    x1_change = snake_block
                    y1_change = 0
                elif event.key == pygame.K_UP:  # 위쪽 화살표 키 입력 시 위쪽으로 이동
                    y1_change = -snake_block
                    x1_change = 0
                elif event.key == pygame.K_DOWN:  # 아래쪽 화살표 키 입력 시 아래쪽으로 이동
                    y1_change = snake_block
                    x1_change = 0

        # 뱀이 화면의 테두리를 넘어갔는지 확인 (충돌 시 게임 종료)
        if x1 >= block_area_right or x1 < block_area_left or y1 >= block_area_bottom or y1 < block_area_top:
            game_close = True  # 게임 종료 플래그 설정

        # 뱀의 새로운 좌표 계산
        x1 += x1_change
        y1 += y1_change
        dis.fill(black)  # 배경을 검은색으로 채움

        # 현재 최고 점수 표시
        display_highest_score()

        # 블록 생성 영역을 구분하기 위해 흰색 테두리를 그림
        pygame.draw.rect(dis, white, [block_area_left, block_area_top, block_area_right - block_area_left, block_area_bottom - block_area_top], 2)

        # 먹이 그리기 (빨간색으로 먹이를 화면에 표시)
        pygame.draw.rect(dis, red, [foodx, foody, snake_block, snake_block])

        # 뱀의 머리 위치 업데이트
        snake_head = []
        snake_head.append(x1)  # 뱀 머리의 x 좌표 추가
        snake_head.append(y1)  # 뱀 머리의 y 좌표 추가
        snake_list.append(snake_head)  # 뱀 리스트에 머리 위치 추가

        if len(snake_list) > length_of_snake:  # 뱀의 길이가 길어졌을 때
            del snake_list[0]  # 꼬리를 제거하여 뱀이 이동하도록 구현

        # 뱀이 자기 몸과 충돌하면 게임 종료
        for x in snake_list[:-1]:
            if x == snake_head:
                game_close = True

        # 뱀을 그리기 (우리 뱀의 각 블록을 화면에 출력)
        our_snake(snake_block, snake_list)
        Your_score(score)  # 현재 점수를 화면에 출력

        pygame.display.update()  # 화면을 업데이트하여 모든 변경사항을 반영

        # 뱀이 먹이를 먹었을 때 처리
        if abs(x1 - foodx) < snake_block and abs(y1 - foody) < snake_block:  # 뱀의 머리가 먹이와 같은 위치에 있을 때
            foodx, foody = generate_food()  # 새로운 먹이를 생성
            length_of_snake += 1  # 뱀의 길이를 증가
            score += 1  # 점수 증가

        # 10초마다 난이도 상승
        if time.time() - last_difficulty_increase_time > 10:  # 마지막 난이도 상승으로부터 10초가 지나면
            current_speed += 2  # 속도를 증가시켜 난이도를 올림
            last_difficulty_increase_time = time.time()  # 마지막 난이도 상승 시간 갱신

        clock.tick(current_speed)  # 현재 속도에 맞춰 게임 속도를 조정

    pygame.quit()  # 게임이 종료되면 Pygame을 종료
    quit()  # 프로그램 종료

# 게임 시작
gameLoop()  # 메인 게임 루프 호출