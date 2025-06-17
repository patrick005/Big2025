#include <zmq.hpp>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cerrno>

using namespace std;
using namespace zmq;

int main(){
    context_t context(1);
    socket_t responder(context, socket_type::rep);
    const char *ipc_file_path = "/tmp/zmq_server";
    
    if (unlink(ipc_file_path) == -1 && errno != ENONET){
        cerr << "IPC 파일을 삭제할 수 없습니다: " << strerror(errno) << endl;
        return 1;
    }
    responder.bind("ipc://" + string(ipc_file_path));
    cout << "서버가 ipc 소켓에 바인딩 되었습니다" << ipc_file_path << endl;

    while(true){
        message_t request;
        recv_result_t result = responder.recv(request, recv_flags::none);
        // 메시지 수신
        if(result && result.value() > 0){
            string received_msg = request.to_string();
            cout << "받은 메시지: " << received_msg << endl; 
            string reply_msg = "[" + received_msg + "]메시지 수신됨"; // echo msg
            responder.send(message_t(reply_msg), send_flags::none);
        } else {
            // 에러 처리
            cerr << "메시지를 수신하는데 실패했습니다" << endl;
            continue;
        }
    }

    return 0;
}