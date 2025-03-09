//test0309.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 10

// 주변의 지뢰 개수 반환
int count_mine(char b[][SIZE], int r, int c){
	int cnt = 0;

	if (r == 0 && c == 0) {				    // (0, 0)
		if (b[r + 1][c] == '#') cnt++;		// right
		if (b[r + 1][c + 1] == '#') cnt++;	// bottom right corner
		if (b[r][c + 1] == '#') cnt++;		// bottom

	}else if (r == 0) {				        // (0, y)
		if (b[r][c - 1] == '#')cnt++;		// top
		if (b[r + 1][c - 1] == '#') cnt++;	// top right corner
		if (b[r + 1][c] == '#') cnt++;		// right
		if (b[r + 1][c + 1] == '#') cnt++;	// bottom right corner
		if (b[r][c + 1] == '#') cnt++;		// bottom

	}else if (c == 0) {				        // (x, 0)
		if (b[r + 1][c] == '#')cnt++;		// right
		if (b[r + 1][c + 1] == '#') cnt++;	// bottom right corner
		if (b[r][c + 1] == '#') cnt++;		// bottom
		if (b[r - 1][c + 1] == '#') cnt++;  // bottom left corner
		if (b[r - 1][c] == '#') cnt++;		// left
	}else if (r == SIZE - 1 && c == SIZE - 1) {	// (9, 9)
		if (b[r][c - 1] == '#') cnt++;		// top
		if (b[r - 1][c - 1] == '#') cnt++;	// top left corner
		if (b[r - 1][c] == '#') cnt++;		// left
	}else if (r == SIZE - 1) {			    // (9, y)
		if (b[r][c - 1] == '#') cnt++;		// top
		if (b[r - 1][c - 1] == '#') cnt++;	// top left corner
		if (b[r - 1][c] == '#')cnt++;		// left
		if (b[r - 1][c + 1] == '#') cnt++;	// bottom left corner
		if (b[r][c + 1] == '#')cnt++;		// bottom
	}else if (c == SIZE - 1) {			    // (x, 9)
		if (b[r][c - 1] == '#') cnt++;		// top
		if (b[r + 1][c - 1] == '#') cnt++;	// top right corner
		if (b[r + 1][c] == '#') cnt++;		// right
		if (b[r - 1][c - 1] == '#') cnt++;	// top left corner
		if (b[r - 1][c] == '#') cnt++;		// left 

	}else {						            // 위 경우가 아니라면 팔방 검사
		if (b[r][c - 1] == '#') cnt++;		// top
		if (b[r + 1][c - 1] == '#') cnt++;	// top right corner
		if (b[r + 1][c] == '#') cnt++;		// right
		if (b[r + 1][c + 1] == '#') cnt++;	// bottom right corner
		if (b[r][c + 1] == '#') cnt++;		// bottom
		if (b[r - 1][c + 1] == '#') cnt++;	// bottom left corner
		if (b[r - 1][c] == '#') cnt++;		// left
		if (b[r - 1][c - 1] == '#') cnt++;	// top left corner
	}
	return cnt;
}

// 주변 지뢰 탐색
void search(char b[][SIZE], int r, int c) {

	if (b[r][c] != '.')
		return;

	if (r < 0 || r > SIZE - 1 || c < 0 || c > SIZE - 1)
		return;

	int cnt = count_mine(b, r, c);
	b[r][c] = cnt;
	
	if (!cnt) {
		search(b, r, c - 1);		// top
		search(b, r + 1, c - 1);	// top right corner
		search(b, r + 1, c);		// right
		search(b, r + 1, c + 1);	// bottom right corner
		search(b, r, c + 1);		// bottom
		search(b, r - 1, c + 1); 	// bottom left corner
		search(b, r - 1, c); 		// left
		search(b, r - 1, c - 1);	// top left corner
	}
}


// 이겼는지 판별
int check_win(char b[][SIZE]){
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (b[i][j] == '.')		// '.'인 요소가 남아있으면 계속 진행
				return 0;
		}
	}
	return 1;
}



// 보드 출력
void print_board(char b[][SIZE]) {

	// 행 번호 출력
	printf("%3c", ' ');
	for (int i = 0; i < SIZE; i++)
		printf(" %d ", i);
	printf("\n");

	for (int i = 0; i < SIZE; i++) {
		printf(" %d ", i); // 열번호 출력
		for (int j = 0; j < SIZE; j++) {

			if (b[i][j] == '#'){
				printf(" _ ");
            }else if (b[i][j] == '.'){
				printf(" _ ");
            }else{
				printf("(%d)", b[i][j]);
            }
		}
		printf("\n");
	}
	printf("\n\n");
}


// 정답 출력
void print_answer(char b[][SIZE]) {

	// 행 번호 출력
	printf("%3c", ' ');
	for (int i = 0; i < SIZE; i++)
		printf(" %d ", i);
	printf("\n");

	for (int i = 0; i < SIZE; i++) {
		printf(" %d ", i); // 열번호 출력
		for (int j = 0; j < SIZE; j++) {
			if (b[i][j] == '#'){
				printf(" # ");
            }else if (b[i][j] == '.'){
				printf(" . ");
            }else{
				printf("(%d)", b[i][j]);
            }
		}
		printf("\n");
	}
	printf("\n\n");
}


int main(){
	int r, c;
	char board[SIZE][SIZE] = { 0 };	// 게임보드 설정
	srand(time(NULL));              // 난수 설정

	// 보드 초기화 및 출력
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if ((rand() % 100) < 15){	// 15%의 확률로 지뢰 세팅
				board[i][j] = '#';		// # : 지뢰
            }else{
				board[i][j] = '.';		// . : 지뢰가 아님
            }
		}
	}
	print_board(board);

	// 게임 시작
	while (1) {

		printf("좌표를 입력하세요 (행, 열) : ");
		scanf("%d %d", &r, &c);
        // scanf_s("%d %d", &r, &c);

		if (board[r][c] == '#') {	// 지뢰를 골랐다면
			printf("\n지뢰가 폭발하였습니다. \n");
			break;
		}else {
			search(board, r, c);
			print_board(board);
		}

		if (check_win(board)) {
			printf("\n!! 성공 !! \n");
			break;
		}

	}
	printf("\n============= 정답 =============\n");
	print_answer(board);

	return 0;

}
