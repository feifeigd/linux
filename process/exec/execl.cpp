#include <unistd.h>
int main(){
    execl("/bin/pwd", "pwd", nullptr);
    return 0;
}
