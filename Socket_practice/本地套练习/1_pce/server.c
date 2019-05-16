#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <stddef.h>

#define SERV_ADDR "serv.socket"

int main(void)
{
    int lfd, cfd, len, size, i;
    struct sockaddr_un serv_addr, clie_addr;
    char buf[4096];

    lfd = socket(AF_UNIX, SOCK_STREAM, 0);

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, SERV_ADDR);

    len = offsetof(struct sockaddr_un, sun_path) + strlen(serv_addr.sun_path);

    unlink(SERV_ADDR);
    bind(lfd, (struct sockaddr *)&serv_addr, len);

    listen(lfd, 20);

    printf("Accept ...\n");
    while(1)
    {
        len = sizeof(clie_addr);
        cfd = accept(lfd, (struct sockaddr *)&clie_addr, (socklen_t *)&len);

        len -= offsetof(struct sockaddr_un, sun_path);
        clie_addr.sun_path[len] = '\0';

        printf("client bind filename %s\n", clie_addr.sun_path);

        while((size = read(cfd, buf, sizeof(buf))) > 0) 
        {
            for (i = 0; i<size; i++)
                buf[i] = toupper(buf[i]);
            write(cfd, buf, size);
        }
        close(cfd);
    }

    close(lfd);
    return 0;
}
