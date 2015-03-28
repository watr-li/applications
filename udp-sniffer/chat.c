#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

#include "thread.h"
#include "socket_base/socket.h"
#include "net_help.h"
#include "chat.h"

#define BUFSZ 250              // TODO: size ok?
#define MAX_CHAN_LEN 10        /* maximum character count of the channel id */

void *chat_udp_server_loop(void *arg);
char chan_name[MAX_CHAN_LEN];

char addr_str[IPV6_MAX_ADDR_STR_LEN];
ipv6_addr_t dest_addr;
uint8_t buf[BUFSZ];
size_t buflen = BUFSZ;






// signatures with all them pointers because it needs
// to be passed to a thread
void *chat_udp_server_loop(void *arg)
{
    sockaddr6_t sa;
    uint8_t buffer_main[UDP_BUFFER_SIZE];
    uint32_t fromlen;
    int sock, resp_code;
    fromlen = sizeof(sa);

    uint8_t scratch_raw[BUFSZ];
    sock = socket_base_socket(PF_INET6, SOCK_DGRAM, IPPROTO_UDP);

    memset(&sa, 0, sizeof(sa));
    sa.sin6_family = AF_INET;
    sa.sin6_port = HTONS(CHAT_PORT);

    if (-1 == socket_base_bind(sock, &sa, sizeof(sa))) {
        printf("UDP Server: Error bind failed!\n");
        socket_base_close(sock);
        return NULL;
    }

    printf("Listening for incoming UDP connection at port %" PRIu16 "\n", CHAT_PORT);

    while (1) {
        int32_t recsize = socket_base_recvfrom(sock, (void *)buffer_main, UDP_BUFFER_SIZE, 0, &sa, &fromlen);
        printf("Received packet!\n");

        if (recsize < 0) {
            printf("ERROR: recsize < 0!\n");
        }

        printf("\n>>>");
        for(int i=0; i<recsize; i++) {
            printf("%02x ", buffer_main[i]);
        }
        printf("\n");
    }

    socket_base_close(sock);
    return NULL;
}
