#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <stddef.h>

#define SERV_ADDR "serv.socket"
#define CLIE_ADDR "clie.socket"

int main(void)
{
    int cfd, len;
    struct sockaddr_un serv_addr, clie_addr;
    char buf[4096];

    cfd = socket(AF_UNIX, SOCK_STREAM, 0);

    bzero(&clie_addr, sizeof(clie_addr));
    clie_addr.sun_family = AF_UNIX;
    strcpy(clie_addr.sun_path, CLIE_ADDR);

    len = offsetof(struct sockaddr_un, sun_path) + strlen(clie_addr.sun_path);

    unlink(CLIE_ADDR);
    bind(cfd, (struct sockaddr *)&clie_addr, len);

    bzero(&serv_addr, sizeof(serv_addr));

    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, SERV_ADDR);

    len = offsetof(struct sockaddr_un, sun_path) + strlen(serv_addr.sun_path);

    connect(cfd, (struct sockaddr *)&serv_addr, len);

    while(fgets(buf, sizeof(buf), stdin) != NULL) 
    {
        write(cfd, buf, strlen(buf));
        len = read(cfd, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, len);
    }

    close(cfd);
    return 0;
}
