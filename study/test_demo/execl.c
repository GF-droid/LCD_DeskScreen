#include <stdio.h>
#include <unistd.h>

int main(){
  execl("/bin/ls", "ls","/home/kali/桌面", NULL);
  return 0;
}
