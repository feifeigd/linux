cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
#add_compile_options(-std=c++11)

subdirs(
	getpid
	forkprocs
	zombie
	thread
)
