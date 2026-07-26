#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {  // 创建socket
        printf("socket fail\n");
        return 1;
    }
    printf("socket success\n");

    // 设置协议族
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // 服务器IP地址
    server_addr.sin_port = htons(8888);               // 转换为网络字节序(大端存储)
    printf("connect success\n");

    // 将 IP 地址从字符串转换为二进制形式并存入server_addr.sin_addr
    // int ret = inet_pton(AF_INET, server_addr.sin_addr.s_addr, &server_addr.sin_addr);
    // if (ret <= 0) {
    //     printf("inet_pton fail");
    //     return 1;
    // }
    printf("inet_pton success\n");

    // 绑定地址
    int ret = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (ret < 0) {
        printf("bind fail\n");
        close(sockfd);  // 关闭socket
        return 1;
    }
    printf("bind success\n");

    // 监听连接
    ret = listen(sockfd, 5);
    if (ret < 0) {
        printf("listen fail\n");
        close(sockfd);  // 关闭socket
        return 1;
    }
    printf("listen success\n");

    // 接受连接
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int connfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_addr_len);
    if (connfd < 0) {
        printf("accept fail\n");
        close(sockfd);  // 关闭socket
        return 1;
    }

    char buf[1024];
    memset(buf, 0, sizeof(buf));
    if (read(connfd, &buf, sizeof(buf)) < 0) {
        printf("read fail\n");
        close(sockfd);  // 关闭socket
        return 1;
    }
    printf("client say: %s\n", buf);

    if (write(connfd, "hello client", sizeof("hello client")) < 0) {
        printf("write fail\n");
        close(sockfd);  // 关闭socket
        return 1;
    }
    printf("write success\n");

    close(connfd);
    close(sockfd);
    printf("close success\n");

    return 0;
}
