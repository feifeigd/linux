
#include <unistd.h>

int main(){
    execl("/bin/ls", "ls", "-al", "/etc/passwd", nullptr);
    return 0;
}