#include <auto_close_fd.h>
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
    auto_close_fd sock { socket(PF_INET, SOCK_STREAM, 0)};
    if(-1 == sock)
        error_handling("socket() error.");

	FILE* fp = fopen("receive.dat", "wb");

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    if(-1 == connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr)))
        error_handling("connect() error.");

    char message[BUFSIZ];
	size_t str_len = 0;
	while ((str_len = read(sock, message, sizeof(message))) > 0) {
		fwrite(message, 1, str_len, fp);
	}
    
    cout << "Received file data";
	write(sock, "Thank you", 10);
	fclose(fp);
    return 0;
}
