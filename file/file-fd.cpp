
#include <iostream>
using namespace std;

int main(){
	cout << "\nfileno(stdin) = "  << fileno(stdin);
	cout << "\nfileno(stdout) = " << fileno(stdout);
	cout << "\nfileno(stderr) = " << fileno(stderr) << endl;
	return 0;
}
