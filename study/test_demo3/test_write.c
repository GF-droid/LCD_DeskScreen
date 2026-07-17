#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
  char* buf = "Hello, World!\n";
  int fd = open("file.txt", O_WRONLY | O_CREAT, 0644);
  if (fd == -1) {
    perror("open");
    _exit(1);
  }
  write(fd, buf, strlen(buf));
  close(fd);
  return 0;
}