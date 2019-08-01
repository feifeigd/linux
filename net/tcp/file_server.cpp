#include <auto_close_fd.h>
#include <unistd.h>	// write
#include <arpa/inet.h>	// sockaddr_in
#include <iostream>

using namespace std;

void error_handling(char const* msg) {
	cerr << msg << endl;
	exit(1);
}

int main(int argc, char* argv[]) {
	if (2 != argc)
	{
		cerr << "Usage: " << argv[0] << " <port>" << endl;
		exit(1);
	}
	FILE* fp = fopen("fu.txt", "rb");
	if (!fp)
	{
		error_handling("open file failed");
	}
	auto_close_fd serv_sd{ socket(PF_INET, SOCK_STREAM, 0) };
	
	sockaddr_in serv_adr{}, clnt_adr{};
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	bind(serv_sd, (sockaddr*)& serv_adr, sizeof(serv_adr));
	listen(serv_sd, 5);

	socklen_t clnt_adr_sz = sizeof(clnt_adr);
	auto_close_fd clnt_sd{ accept(serv_sd, (sockaddr*)& clnt_adr, &clnt_adr_sz) };
	char buf[BUFSIZ];
	while (true)
	{
		size_t read_cnt = fread(buf, 1, BUFSIZ, fp);
		if (read_cnt < BUFSIZ)
		{
			write(clnt_sd, buf, read_cnt);
			break;
		}
		write(clnt_sd, buf, BUFSIZ);
	}
	shutdown(clnt_sd, SHUT_WR);
	ssize_t len = read(clnt_sd, buf, BUFSIZ);
	buf[len] = 0;
	cout << "Message from client: " << buf << endl;
	fclose(fp);
	return 0;
}
