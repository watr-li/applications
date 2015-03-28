#ifndef SNIFFER_H
#define SNIFFER_H

#include "kernel.h"
#include "ipv6.h"

#define IF_ID               (0)
#define CHAT_PORT           (12345)
#define UDP_BUFFER_SIZE     (128)
#define SNIFFER_BUFFER_SIZE (250)

void *udp_server_loop(void *arg);

#endif /* SNIFFER_H */
