cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
#add_compile_options(-std=c++11)

subdirs(
	coroutine
	getpid
    net
	process
	"file"
	forkprocs
	zombie
	thread
)
