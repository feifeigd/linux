
#pragma once

#include <unistd.h> // close

class auto_close_fd{
    int _fd;
    auto_close_fd(auto_close_fd const&) = delete;
    auto_close_fd& operator=(auto_close_fd const&) = delete;
public:
    auto_close_fd(int fd):_fd(fd){}
    ~auto_close_fd(){
        if(-1 != _fd)
            close(_fd);
    }
    operator int(){
        return _fd;
    }

};

