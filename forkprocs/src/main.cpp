
#include <iostream>
#include <unistd.h>
using namespace std;

int main(){
	int i = 1;
	cout << "The main program process ID is " << getpid() << endl;
	pid_t child_pid = fork();	// 创建子进程, 返回子进程id
	if (child_pid)	// 
	{
		i = 0;
		cout << "This is the parent process, with id " << getpid() << " and i = " << i << endl;
	}
	else
	{
		cout << "This is the child process, with id " << getpid() << " and i = " << i << endl;
	}
	
	return 0;
}
