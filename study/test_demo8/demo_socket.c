#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int client_fd;
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {  // 创建socket
        printf("socket fail\n");
        return 1;
    }
    printf("socket success\n");

    // 设置协议族
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);  // 转换为网络字节序(大端存储)
    printf("connect success\n");

    // 将 IP 地址从字符串转换为二进制形式并存入server_addr.sin_addr
    int ret = inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    if (ret <= 0) {
        printf("inet_pton fail\n");
        return 1;
    }
    printf("inet_pton success\n");

    ret = connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (ret < 0) {
        printf("connect fail\n");
        close(client_fd);  // 关闭socket
        return 1;
    }
    printf("connect success\n");

    // 发送消息
    if (write(client_fd, "hello client", sizeof("hello client")) < 0) {
        printf("write fail\n");
        close(client_fd);  // 关闭socket
        return 1;
    }
    printf("write success\n");

    // 读取服务器回复
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    if (read(client_fd, &buf, sizeof(buf)) < 0) {
        printf("read fail\n");
        close(client_fd);  // 关闭socket
        return 1;
    }
    printf("client say: %s\n", buf);

    close(client_fd);
    printf("close success\n");

    return 0;
}
