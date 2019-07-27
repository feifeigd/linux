

#include <sys/socket.h>
#include <iostream>
#include <string>
using namespace std;

void error_handling(string const& msg) {
	cerr << msg << endl;
	exit(1);
}

int main(int argc, char* argv[]) {
	if (argc != 2)
	{
		cerr << "Usage: " << argv[0] << " <port>" << endl;
		exit(1);
	}
	int serv_sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (-1 == serv_sock) {
		error_handling("UDP socket creation error.");
	}

	sockaddr_in serv_adr{}, clnt_adr{};
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	if (-1 == bind(serv_sock, (sockaddr*)& serv_adr, sizeof(serv_adr))) {
		error_handling("bind() error.");
	}

	// 暂时是个死循环
	while (true) {
		socklen_t clnt_adr_sz = sizeof(clnt_adr);
		int str_len = recvfrom(serv_sock, message, BUF_SIZE, 0, (sockaddr*)& clnt_adr, &clnt_adr_sz);
		cout << "recv data:" << message << endl;
		sendto(serv_sock, message, str_len, 0, (sockaddr*)& clnt_adr, &clnt_adr_sz);
	}
	close(serv_sock);
	return 0;
}
