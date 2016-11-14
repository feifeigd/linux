
#include <iostream>
#include <unistd.h>
using namespace std;

int main(){
	cout << "The process ID is " << getpid() << endl;
	cout << "The parent process ID is " << getppid() << endl;
	return 0;
}
