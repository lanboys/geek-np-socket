#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define SERVER_PORT 12345

ssize_t readn(int, void *, size_t);

void read_data(int);

int main(int argc, char **argv) {
    int listenfd, connfd;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERVER_PORT);

    bind(listenfd, (const struct sockaddr *) &servaddr, sizeof(servaddr));
    listen(listenfd, 1024);

    for (;;) {
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (const struct sockaddr *) &cliaddr, &clilen);
        read_data(connfd);
        close(connfd);          /* 关闭连接套接字，注意不是监听套接字*/
    }
    return 0;
}

void read_data(int sockfd) {
    ssize_t n;
    int size = 1024;
    char buf[size];

    int time = 0;
    for (;;) {
        fprintf(stdout, "******* block in read *******\n");

        memset(buf, 0, sizeof buf);
        if ((n = readn(sockfd, (void *) buf, (size_t) size)) == 0)
            return;
        time++;
        //fprintf(stdout, "1K read for %d \n", time);
        //fprintf(stdout, "buf value : %s \n\n\n", buf);
        fprintf(stdout, "buffer value : ");
        for (int i = 0; i < size; i++) {
            char *t = buf + i;
            printf("%c", *t);
        }
        fprintf(stdout, "\n\n\n");
        sleep(1);
    }
}

ssize_t readn(int fd, void *vptr, size_t size) {
    size_t nleft;
    ssize_t nread;
    char *ptr;
    char *ptrPrint;

    ptr = vptr;
    nleft = size;

    while (nleft > 0) {
        if ((nread = read(fd, ptr, nleft)) < 0) {
            if (errno == EINTR)
                nread = 0;
            else
                return (-1);
        } else if (nread == 0) {
            break;
        }
        nleft -= nread;
        ptrPrint = ptr;
        ptr += nread;
        fprintf(stdout, "--- required: %d, read: %d, left: %d\n", size, nread, nleft);
        printf("--- read recv: %s \n", ptrPrint);
    }
    return size - nleft;
}

