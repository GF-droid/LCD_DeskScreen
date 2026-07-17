#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

size_t SIZEBUFFER = 100;

int main() {
  char* buf = "Hello, World!\n";
  char* read_buf = malloc(sizeof(char) * SIZEBUFFER);
  if (!read_buf) {
    perror("malloc");
    _exit(1);
  }

  int fd = open("file.txt", O_RDWR | O_CREAT, 0644);
  if (fd == -1) {
    perror("open");
    _exit(1);
  }

  ssize_t bytes_written = write(fd, buf, strlen(buf));
  printf("Wrote %zd bytes: %zd\n", bytes_written, strlen(buf));
  if (bytes_written == -1) {
    perror("write");
    _exit(1);
  }

  off_t pos = lseek(fd, 0, SEEK_SET);
  if (pos == -1) {
    perror("lseek");
    _exit(1);
  }

  ssize_t bytes_read = read(fd, read_buf, SIZEBUFFER - 1);
  if (bytes_read == -1) {
    perror("read");
    _exit(1);
  }

  read_buf[bytes_read] = '\0'; // Null-terminate the read buffer

  printf("Read %zd bytes: %.*s\n", bytes_read, (int)bytes_read, read_buf);

  close(fd);
  free(read_buf);
  return 0;
}