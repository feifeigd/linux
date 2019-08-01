
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>	// waitpid
#include <bits/sigset.h>	// sigset_t
using namespace std;

void sigchld_handler(int signo);
	
int main(){	
	cout << "The main program process ID is " << getpid() << endl;
	struct sigaction newact, oldact;
	newact.sa_handler = sigchld_handler;	// 设置信号处理程序
	newact.sa_flags = 0;	// 无特殊选项
	if (-1 == sigemptyset(&newact.sa_mask)
	    || -1 == sigaction(SIGCHLD, &newact, &oldact))// 子进程状态发生变化
		perror("Failed to set SIGCHLD.");
	for (size_t i = 0; i < 2; ++i)	// fork 5个子进程
	{
		pid_t child_pid = fork();	// 创建子进程, 返回子进程id
		if (child_pid)	// 
		{
			cout << "This is the parent process, with id " << getpid() << endl;
			cout << "Main thread sleep 60 second." << endl;
			sleep(20);
		}
		else
		{
			cout << "This is the child process, with id " << getpid() << endl;
			cout << "Child thread exit." << endl;
			break;
		}
	}
	
	return 0;
}

//子进程退出的异步善后处理
void sigchld_handler(int signo)	
{
	if (SIGCHLD != signo)	// 子进程终止
	{
		return;
	}
	// 等待已退出的所有子进程
	pid_t pid {};
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
