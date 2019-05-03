
#include <cstdio>
#include <cstdlib> // exit
#include <fcntl.h>  // O_APPEND
#include <unistd.h> // write
#include <csignal> // signal
#include <sys/stat.h> // umask
#include <string.h> // strlen

#define MAXFILE 65535

volatile sig_atomic_t g_running = true;
void sigterm_handler(int arg){
    g_running = false;
}
int main(){
    pid_t pc = fork();
    if(pc < 0){
        printf("error fork\n");
        exit(1);
    }else if( pc > 0 )
        exit(0); // 退出主进程

    setsid();   // 第二步
    chdir("/"); // 第三步
    umask(0);   // 第四步
    for(int i = 0; i < MAXFILE; ++i)
        close(i);
    signal(SIGTERM, sigterm_handler);
    while(g_running){
        int fd = -1;
        if((fd = open("/tmp/dameon.log", O_CREAT | O_WRONLY | O_APPEND, 0600)) < 0){
            perror("open");
            exit(1);
        }
        char const* buf = "this is a Dameon\n";
        size_t len = strlen(buf);
        write(fd, buf, len + 1);
        close(fd);
        usleep(1 * 60 * 1000);  // 1 分钟
    }
    return 0;
}

