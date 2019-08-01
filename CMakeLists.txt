cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    common
)
subdirs(
	coroutine
	getpid
	ipc
    net
	process
	"file"
	forkprocs
	zombie
	thread
)
