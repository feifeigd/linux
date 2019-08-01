
#include <unistd.h>
#include <iostream>
using namespace std;

// 双向通信
int main() {
	int fds1[2], fds2[2];
	pipe(fds1); pipe(fds2);
	char buf[BUFSIZ];
	pid_t pid = fork();
	if (0 == pid)	// 子进程
	{
		char str[] = "Who are you?";
		write(fds1[1], str, sizeof(str));
		//sleep(2);
		int len = read(fds2[0], buf, BUFSIZ);
		buf[len] = 0;
		cout << "Child proc output: " << buf << endl;
	}
	else
	{
		int len = read(fds1[0], buf, BUFSIZ);
		buf[len] = 0;
		cout << "Parent proc output: " << buf << endl;
		char str[] = "Thank you for your message";
		write(fds2[1], str, sizeof(str));
		sleep(3);
	}
	return 0;
}
