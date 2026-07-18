#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// 匿名管道只适合给有关系的两个进程使用，并且是半双工通信，只适合小信号量的数据传输

int main() {
  int pipefd[2];
  if(pipe(pipefd) == -1) {  // 创建匿名管道
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  __pid_t pid = fork();
  if(pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if(pid == 0) { // Child process
    close(pipefd[1]); // Close unused write end
    char buffer[100];
    read(pipefd[0], buffer, sizeof(buffer));
    printf("Child received: %s\n", buffer);
    close(pipefd[0]);
  } else { // Parent process
    close(pipefd[0]); // Close unused read end
    const char *message = "Hello from parent!";
    write(pipefd[1], message, strlen(message) + 1);
    close(pipefd[1]);

  }

  return 0;
}
