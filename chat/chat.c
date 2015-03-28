#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

#include "thread.h"
#include "socket_base/socket.h"
#include "net_help.h"
#include "chat.h"

char addr_str[IPV6_MAX_ADDR_STR_LEN];

void chat_say(int argc, char **argv)
{
    if (argc != 2) {
        puts("! Invalid number of parameters");
        printf("  usage: %s <message>\n", argv[0]);
        return;
    }

    ipv6_addr_t dest_addr;
    ipv6_addr_init(&dest_addr, 0xff02, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1);
    chat_udp_send(&dest_addr, CHAT_PORT, argv[1], strlen(argv[1]));
}

void chat_join(int argc, char **argv)
{

}


void chat_udp_send(ipv6_addr_t *dest, uint16_t port, char *payload, size_t len)
{
    int sock;
    sockaddr6_t sa;
    int bytes_sent;

    sock = socket_base_socket(PF_INET6, SOCK_DGRAM, IPPROTO_UDP);

    if (-1 == sock) {
        printf("Error Creating Socket!");
        return;
    }
    memset(&sa, 0, sizeof(sa));
    sa.sin6_family = AF_INET;
    memcpy(&sa.sin6_addr, dest, 16);
    sa.sin6_port = HTONS(port);

    printf("Trying to send %i bytes to %s:%" PRIu16 "\n", len,
           ipv6_addr_to_str(addr_str, IPV6_MAX_ADDR_STR_LEN, dest), port);
    bytes_sent = socket_base_sendto(sock, payload, len, 0, &sa, sizeof(sa));

    if (bytes_sent < 0) {
        printf("Error sending packet!\n");
    }
    else {
        printf("Successful deliverd %i bytes over UDP to %s to 6LoWPAN\n",
               bytes_sent, ipv6_addr_to_str(addr_str, IPV6_MAX_ADDR_STR_LEN, dest));
    }

    socket_base_close(sock);
}

// signatures with all them pointers because it needs
// to be passed to a thread
void *chat_udp_server_loop(void *arg)
{
    sockaddr6_t sa;
    char buffer_main[UDP_BUFFER_SIZE];
    uint32_t fromlen;
    int sock;
    fromlen = sizeof(sa);

    sock = socket_base_socket(PF_INET6, SOCK_DGRAM, IPPROTO_UDP);

    memset(&sa, 0, sizeof(sa));
    sa.sin6_family = AF_INET;
    sa.sin6_port = HTONS(CHAT_PORT);

    if (-1 == socket_base_bind(sock, &sa, sizeof(sa))) {
        printf("UDP Server: Error bind failed!\n");
        socket_base_close(sock);
        return;
    }

    printf("Listening for incoming UDP connection at port %" PRIu16 "\n", CHAT_PORT);

    while (1) {
        int32_t recsize = socket_base_recvfrom(sock, (void *)buffer_main, UDP_BUFFER_SIZE, 0, &sa, &fromlen);

        if (recsize < 0) {
            printf("ERROR: recsize < 0!\n");
        }

        printf("UDP packet received, payload: %s\n", buffer_main);
    }

    socket_base_close(sock);
    return;
}
