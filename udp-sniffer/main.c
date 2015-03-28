#include <stdio.h>

#include "kernel.h"
#include "thread.h"
#include "net_if.h"
#include "posix_io.h"
#include "shell.h"
#include "shell_commands.h"
#include "board_uart0.h"

#include "sniffer.h"

char udp_server_stack_buffer[KERNEL_CONF_STACKSIZE_MAIN];
kernel_pid_t udp_server_pid;

int main(void)
{
    sixlowpan_lowpan_init_interface(IF_ID);

    udp_server_pid = thread_create(udp_server_stack_buffer,
                                             sizeof(udp_server_stack_buffer),
                                             PRIORITY_MAIN, CREATE_STACKTEST,
                                             udp_server_loop, NULL,
                                             "udp_server_loop");
}
