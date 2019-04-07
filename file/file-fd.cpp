
#include <iostream>
using namespace std;

// FILE*转fd
// int fileno(FILE* stream);
// fd 转 FILE*
// FILE* fdopen(int fd, char const* mode);
int main(){
	cout << "\nfileno(stdin) = "  << fileno(stdin);
	cout << "\nfileno(stdout) = " << fileno(stdout);
	cout << "\nfileno(stderr) = " << fileno(stderr) << endl;
	return 0;
}
