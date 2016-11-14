cmake_minimum_required(VERSION 3.0)

add_compile_options(-std=c++0x)

subdirs(
	getpid
	forkprocs
)
