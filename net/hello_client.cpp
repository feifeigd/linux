#include <unistd.h> // read
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
using namespace std;

void error_handling(char const* msg){
    cerr << msg << endl;
    exit(1);
}

int main(int argc, char* argv[]){
    if(3 != argc){
        cerr << "Usage : " << argv[0] << " <IP> <port>" << endl;        
        exit(1);
    }
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if(-1 == sock)
        error_handling("socket() error.");
    sockaddr_in serv_addr = {};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    if(-1 == connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr)))
        error_handling("connect() error.");
    char message[128];
    size_t str_len = read(sock, message, sizeof(message));
    if(-1 == str_len)
        error_handling("read() error.");

    cout << "Message from server : " << message << endl;
    close(sock);

    return 0;
}
