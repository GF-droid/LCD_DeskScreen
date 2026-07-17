#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

  __pid_t pid = fork();
  if (pid == -1) {
    perror("fork");
    _exit(1);
  }

  if (pid == 0) {
    printf("Child process: PID = %d, PPID = %d\n", getpid(), getppid());
    sleep(5); // Sleep for a second to ensure the child process runs first
    printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
    return 1;
  } else {
    int status;
    waitpid(pid, &status, 0);
    printf("Child process finished with status %d\n", status);
    printf("Child process finished with status %d\n", WEXITSTATUS(status));
    printf("Parent process is waiting for the child to finish...\n");
  }

  return 0;
}
