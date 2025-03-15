#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mysql/mysql.h>

#define FRAMES 10

typedef struct {
    int try1;
    int try2;
    int score;
} Frame;

typedef struct {
    char name[40];
    Frame frames[FRAMES];
    int totalScore;
} Player;

void printMenu();
void startGame();
void updateDatabase(Player *player);
void printScoreboard(Player *player);

int main() {
    int choice;
    while (1) {
        printMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 0: startGame(); break;
            case 1: printf("랭킹 기능 준비 중\n"); break;
            case 2: printf("게임을 종료합니다.\n"); return 0;
            default: printf("잘못된 입력입니다. 다시 선택하세요.\n");
        }
    }
    return 0;
}

void printMenu() {
    printf("=== 볼링 게임 ===\n");
    printf("0. 1인용 게임 시작\n");
    printf("1. 랭킹 확인\n");
    printf("2. 게임 종료\n");
    printf("선택: ");
}

void startGame() {
    Player player;
    player.totalScore = 0;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    printf("플레이어 이름을 입력하세요: ");
    scanf("%s", player.name);
    
    for (int frame = 0; frame < FRAMES; frame++) {
        printf("%d 프레임 - 첫 번째 투구 (0-10): ", frame + 1);
        do {
            scanf("%d", &player.frames[frame].try1);
        } while (player.frames[frame].try1 < 0 || player.frames[frame].try1 > 10);
        
        if (player.frames[frame].try1 == 10) {
            printf("스트라이크!\n");
            player.frames[frame].try2 = -1;
        } else {
            printf("%d 핀 남음, 두 번째 투구 (0-%d): ",
                   10 - player.frames[frame].try1,
                   10 - player.frames[frame].try1);
            do {
                scanf("%d", &player.frames[frame].try2);
            } while (player.frames[frame].try2 < 0 || player.frames[frame].try2 > (10 - player.frames[frame].try1));
        }
        
        player.frames[frame].score = player.frames[frame].try1 + (player.frames[frame].try2 == -1 ? 0 : player.frames[frame].try2);
        player.totalScore += player.frames[frame].score;
        printScoreboard(&player);
    }
    
    updateDatabase(&player);
}

void printScoreboard(Player *player) {
    printf("| ");
    for (int i = 0; i < FRAMES; i++) {
        if (player->frames[i].try1 == 0 && player->frames[i].try2 == 0) {
            printf("   |   ");
        } else {
            printf(" %2d | %2d |", player->frames[i].try1, player->frames[i].try2 == -1 ? 0 : player->frames[i].try2);
        }
    }
    printf(" Final: %d\n", player->totalScore);
}

void updateDatabase(Player *player) {
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        printf("MySQL 초기화 실패\n");
        return;
    }
    if (!mysql_real_connect(conn, "localhost", "root", "", "bowling", 0, NULL, 0)) {
        printf("MySQL 연결 실패: %s\n", mysql_error(conn));
        return;
    }
    
    char query[256];
    sprintf(query, "INSERT INTO score (name, score, date) VALUES ('%s', %d, CURDATE())", player->name, player->totalScore);
    mysql_query(conn, query);
    
    sprintf(query, "INSERT INTO visit (name, dateMonth, counting) VALUES ('%s', DATE_FORMAT(CURDATE(), '%%Y-%%m'), 1) ON DUPLICATE KEY UPDATE counting = counting + 1", player->name);
    mysql_query(conn, query);
    
    sprintf(query, "INSERT INTO total (name, score, date, counting) VALUES ('%s', %d, CURDATE(), 1) ON DUPLICATE KEY UPDATE score = score + %d, counting = counting + 1", player->name, player->totalScore, player->totalScore);
    mysql_query(conn, query);
    
    mysql_close(conn);
}
