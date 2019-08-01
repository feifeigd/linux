#include <auto_close_fd.h>
#include <unistd.h>	// write
#include <arpa/inet.h>	// sockaddr_in
#include <iostream>
#include <csignal>	// sigaction
#include <sys/wait.h>	// waitpid
using namespace std;

void error_handling(char const* msg) {
	cerr << msg << endl;
	exit(1);
}

//子进程退出的异步善后处理
void sigchld_handler(int signo)
{
	if (SIGCHLD != signo)	// 子进程终止
	{
		return;
	}
	// 等待已退出的所有子进程
	pid_t pid{};
	int status = 0;
	do
	{
		pid = waitpid(-1, &status, WNOHANG);	// wait函数会阻塞，waitpid不阻塞
		if (WIFEXITED(status))	// 子进程正常终止
		{
			cout << "Removed proc id: " << pid << "\n"
				<< "Child send: " << WEXITSTATUS(status) << endl;	// 子进程的返回值
		}
		cout << "pid exit:" << pid << endl;
	} while (pid > 0);
}

int main(int argc, char* argv[]) {
	if (2 != argc)
	{
		cerr << "Usage: " << argv[0] << " <port>" << endl;
		exit(1);
	}
	struct sigaction newact, oldact;
	newact.sa_handler = sigchld_handler;	// 设置信号处理程序
	newact.sa_flags = 0;	// 无特殊选项
	if (-1 == sigemptyset(&newact.sa_mask)
		|| -1 == sigaction(SIGCHLD, &newact, &oldact))// 子进程状态发生变化
		perror("Failed to set SIGCHLD.");

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
	char buf[BUFSIZ];
	while (true)
	{
		auto_close_fd clnt_sd{ accept(serv_sd, (sockaddr*)& clnt_adr, &clnt_adr_sz) };
		if (-1 == clnt_sd)
		{
			continue;
		}
		cout << "new client connected...\n";
		pid_t pid = fork();
		if (-1 == pid)
			continue;
		if (0 == pid) {	// 子进程区域
			size_t read_cnt = 0;
			while((read_cnt = fread(buf, 1, BUFSIZ, fp)) > 0);
				write(clnt_sd, buf, read_cnt);
			cout << "client disconnected..." << endl;
			break ; // 退出子进程
		}
	}
	fclose(fp);
	return 0;
}
