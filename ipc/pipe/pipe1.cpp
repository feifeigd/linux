
#include <unistd.h>
#include <iostream>
using namespace std;

// 单向通信
int main() {
	int fds[2];
	pipe(fds);
	pid_t pid = fork();
	if (0 == pid)	// 子进程
	{
		char str[] = "Who are you?";
		write(fds[1], str, sizeof(str));
	}
	else
	{
		char buf[BUFSIZ];
		int len = read(fds[0], buf, BUFSIZ);
		buf[len] = 0;
		cout << buf << endl;
	}
	return 0;
}
