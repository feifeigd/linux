
#include <iostream>
#include <unistd.h>
using namespace std;

int main(){
	int i = 1;
	cout << "The main program process ID is " << getpid() << endl;
	pid_t child_pid = fork();	// 创建子进程, 返回子进程id
	if (child_pid)	// 
	{
		cout << "Main thread sleep 60 second." << endl;
		sleep(60);
	}
	else
	{
		cout << "Child thread exit." << endl;
	}
	
	return 0;
}
