#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

void error_handling(string const& msg) {
	cerr << msg << endl;
	exit(1);
}

#define BUF_SIZE 100

int main(int argc, char* argv[]) {
	if (argc != 3)
	{
		cerr << "Usage: " << argv[0] << " <IP> <port>" << endl;
		exit(1);
	}
	int sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (-1 == sock) {
		error_handling("socket() error");
	}

	sockaddr_in serv_adr{};
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_adr.sin_port = htons(atoi(argv[2]));
	// 连接udp 
	int ret = connect(sock, (sockaddr*)& serv_adr, sizeof(serv_adr));
	char message[BUF_SIZE];

	while (true)
	{
		cout << "Inert message(q to quit): ";
		cin >> message;
		if (!strcmp(message, "q") || !strcmp(message, "Q"))
		{
			break;
		}
		send(sock, message, strlen(message), 0);
		int str_len = recv(sock, message, BUF_SIZE, 0);
		message[str_len] = 0;
		cout << "Message from server: " << message << endl;
	}
	close(sock);
	return 0;
}
