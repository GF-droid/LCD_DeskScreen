#include <stdio.h>
#include <unistd.h>

typedef struct{
  char username[20];
  int password;
  int email;
} User;

int main() {
  User userwrite = {"kali", 123456, 123456};
  User userread;

  FILE *fp = fopen("user.txt", "w+");
  if (fp == NULL) {
    perror("Failed to open file");
    return 1;
  }

  fwrite(&userwrite, sizeof(User), 1, fp);
  rewind(fp);
  fread(&userread, sizeof(User), 1, fp);
  printf("Username: %s, Password: %d, Email: %d\n", userread.username, userread.password, userread.email);
  fclose(fp);
  return 0;
}
