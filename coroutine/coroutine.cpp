
// void makecontext(ucontext_t *ucp, void (*func)(), int argc, ...);
// int swapcontext(ucontext_t *oucp, ucontext_t *ucp); 
#include <ucontext.h>

#include <iostream>
using namespace std;

static ucontext_t uctx_main, uctx_func1, uctx_func2;

#define handle_error(msg) do{perror(msg); exit(EXIT_FAILURE);}while(0)

static void func1(void){
	cout << "func1: started\n"
		<< "func1: swapcontext(&uctx_func1, &uctx_func2)\n";
	if(-1 == swapcontext(&uctx_func1, &uctx_func2))
		handle_error("swapcontext");
	cout << "func1: returning\n";
}

static void func2(void){
	cout << "func2: started\n"
		<< "func2: swapcontext(&uctx_func2, &uctx_func1)\n";
	if(-1 == swapcontext(&uctx_func2, &uctx_func1))
		handle_error("swapcontext");
	cout << "func2: returning\n";
}

int main(int argc, char* argv[]){
	char func1_stack[16384];
	char func2_stack[16384];

	if(-1 == getcontext(&uctx_func1))
		handle_error("getcontext");
	uctx_func1.uc_stack.ss_sp = func1_stack;
	uctx_func1.uc_stack.ss_size = sizeof(func1_stack);
	uctx_func1.uc_link = &uctx_main;
	makecontext(&uctx_func1, func1, 0);

	if(-1 == getcontext(&uctx_func2))
		handle_error("getcontext");
	uctx_func2.uc_stack.ss_sp = func2_stack;
	uctx_func2.uc_stack.ss_size = sizeof(func2_stack);
	uctx_func2.uc_link = argc > 1 ? nullptr : &uctx_main;
	makecontext(&uctx_func2, func2, 0);

	cout << "main: swapcontext(&uctx_main, &uctx_func2)\n";
	if(-1 == swapcontext(&uctx_main, &uctx_func2))
		handle_error("swapcontext");
	
	cout << "main: exiting" << endl;
	return EXIT_SUCCESS;
}
