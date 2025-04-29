//op_server.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 1024

void error_handling(char *message);
int calculate(int opnum, int opnds[], char op);

int main(int argc, char *argv[]){
    int serv_sock;
    int clnt_sock;
    int str_len;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;
    
    if (argc != 2){
        printf("사용법: %s <PORT>\n", argv[0]);
        exit(1);
    }
    
    serv_sock = socket(PF_INET, SOCK_STREAM, 0); // tcp setting
    if (serv_sock == -1){
        error_handling("socket() error");
    }
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    
    int option = 1;
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1){
        error_handling("bind() error");
    }
    if(listen(serv_sock, 5)){
        error_handling("listen() error");
    } // 5개의 클라이언트 대기
    
    int opnd_cnt = 0;
    int recv_len = 0, recv_cnt;
    char opinfo[BUF_SIZE];
    int result;
    
    for(int i = 0; i < 20; ++i){
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
        if (clnt_sock == -1){
            error_handling("accept() error");
        }else{
            printf("connected client %d : %s \n", i + 1, inet_ntoa(clnt_addr.sin_addr));
        }
        
        // 연결된 상태의 코드....
        read(clnt_sock, &opnd_cnt, 1); // 몇개 들어올지 1 byte로 받음
        // printf("피연산자 갯수: %d \n", opnd_cnt);                           //debugging message --> 여기까진 오는디?
        recv_len = 0; // while에 남은 값 들어갈 수 있기에 초기화

        while((opnd_cnt * 4 + 1) > recv_len){
            recv_cnt = read(clnt_sock, &opinfo[recv_len], BUF_SIZE - 1);
            recv_len += recv_cnt;
        }
        result = calculate(opnd_cnt, (int*)opinfo, opinfo[recv_len - 1]);
        write(clnt_sock, (char*)&result, sizeof(result));
        close(clnt_sock);
    }

    close(serv_sock);
    return 0;
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int calculate(int opnum, int opnds[], char op){
    int result = opnds[0], i;
    switch(op){
        case '+':
            for(i = 1; i < opnum; ++i){
                result += opnds[i];
            }
            break;
        case '-':
            for(i = 1; i < opnum; ++i){
                result -= opnds[i];
            }
            break;
        case '*':
            for(i = 1; i < opnum; ++i){
                result *= opnds[i];
            }
            break;
        /*case '/':
            for(i = 1; i < opnum; ++i){
                result /= opnds[i];
            }
            break;*/
    }
    return result;
}
//./echo_server 8890
/*
  netstat -tulnp
  kill 28534
  kill -9 28534
  kill -9 3180
  kill -9 29628
  history


*/