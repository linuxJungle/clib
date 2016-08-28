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

    des.host_name = "www.oschina.net";
    des.host_port = 80;
    des.uri = "/";
    sockfd = http_get (&des);
    if (sockfd == -1) {
        printf("error.\n");
        exit(-1);
    }
    http_parse_response (sockfd, &res);
    code = res->status_code;
    status_message = res->status_message;
    http_hdr_t *header = res->header;
    const char *value = http_header_get(header, "Server");
    size_t content_len = res->content_len;
    const char *content = res->content;
    printf("%d\t%s\t%s\t%d\n", code, status_message, value, content_len);
    printf("%s\n", content);

    http_destroy_response(res);

    close(sockfd);

    return 0;
}
