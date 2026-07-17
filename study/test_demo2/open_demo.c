#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
  int fd = open("file.txt", O_WRONLY|O_CREAT, 0644);
  if(fd == -1){
    perror("open");
    _exit(1);
  }
  close(fd);

  return 0;
}
