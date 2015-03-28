#ifndef CHAT_H
#define CHAT_H

#include "kernel.h"
#include "ipv6.h"

#define CHAT_PORT (12345)

/**
 * @brief   Which interface should be used for 6LoWPAN
 */
#define IF_ID   (0)

#define UDP_BUFFER_SIZE     (128)

/**
 * @brief   Helper variable for IP address printing
 */
extern char addr_str[IPV6_MAX_ADDR_STR_LEN];

void *chat_udp_server_loop(void *arg);
void chat_init(void);

#endif /* CHAT_H */
