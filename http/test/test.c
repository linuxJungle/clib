#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "http.h"

int
main (void)
{
    http_des_t  des;
    http_res_t *res;
    int         code;
    int         sockfd;
    const char *status_message;

    des.host_name = "localhost";
    des.host_port = 80;
    des.uri = "/a.php";
    sockfd = http_get (&des);
    if (sockfd == -1) {
        printf("error.\n");
        exit(-1);
    }
    http_parse_response (sockfd, &res);
    code = res->status_code;
    status_message = res->status_message;
    printf("%d\t%s\n", code, status_message);

    http_destroy_response(res);

    close(sockfd);

    return 0;
}
