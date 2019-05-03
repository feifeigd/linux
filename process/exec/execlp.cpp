#include <unistd.h>

int main(){
    // 不需要写绝对路径，会从path查找
    execlp("pwd", "", nullptr);
    return 0;
}
