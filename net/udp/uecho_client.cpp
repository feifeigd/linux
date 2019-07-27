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

	sockaddr_in serv_adr{}, from_adr{};
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_adr.sin_port = htons(atoi(argv[2]));

	char message[BUF_SIZE];

	while (true)
	{
		cout << "Inert message(q to quit): ";
		cin >> message;
		if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
		{
			break;
		}
		sendto(sock, message, strlen(message), 0, (sockaddr*)& serv_adr, sizeof(serv_adr));
		socklen_t adr_sz = sizeof(from_adr);
		int str_len = recvfrom(sock, message, BUF_SIZE, 0, (sockaddr*)& from_adr, &adr_sz);
		message[str_len] = 0;
		cout << "Message from server: " << message;
	}
	close(sock);
	return 0;
}
