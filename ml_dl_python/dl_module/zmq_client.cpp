#include <zmq.hpp>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cerrno>
#include <time.h>


using namespace std;
using namespace zmq;

int main(){
    context_t context(1);
    socket_t requester(context, socket_type::req);
    const char *ipc_file_path = "/tmp/zmq_server";
    requester.connect("ipc://" + string(ipc_file_path));
    cout << "클라이언트가 ipc 소켓에 연결 되었습니다" << ipc_file_path << endl;
    int request_count  = 0;

    while(true){
        string request_str = "클라이언트에서 간다~" + to_string(request_count++);
        message_t request_msg(request_str.begin(), request_str.end());
        recv_result_t result = requester.send(request_msg, send_flags::none);
        
        message_t reply_msg;
        recv_result_t reply_result = requester.recv(reply_msg, recv_flags::none);

        if(reply_result && reply_result.value() > 0){
            string reply_str = reply_msg.to_string();
            cout << "서버로부터 받은 메시지: " << reply_str << endl;
        } else {
            cerr << "서버로부터 응답을 받지 못했습니다" << endl;
        }
        // 2초 대기
        sleep(2);        
    }

    return 0;
}