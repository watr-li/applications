#include <stdio.h>

#include "kernel.h"
#include "thread.h"
#include "net_if.h"
#include "posix_io.h"
#include "shell.h"
#include "shell_commands.h"
#include "board_uart0.h"

#include "chat.h"

const shell_command_t shell_commands[] = {
    {"say", "Send a message on the current channel", chat_say},
    {"join", "Switch to another channel", chat_join},
    {NULL, NULL, NULL}
};

char udp_server_stack_buffer[KERNEL_CONF_STACKSIZE_MAIN];

kernel_pid_t chat_udp_server_pid;

int main(void)
{
    sixlowpan_lowpan_init_interface(IF_ID);

    /* Start the UDP server thread */
    chat_udp_server_pid = thread_create(udp_server_stack_buffer,
                                             sizeof(udp_server_stack_buffer),
                                             PRIORITY_MAIN, CREATE_STACKTEST,
                                             chat_udp_server_loop, NULL,
                                             "chat_udp_server_loop");

    /* Open the UART0 for the shell */
    posix_open(uart0_handler_pid, 0);

    shell_t shell;
    shell_init(&shell, shell_commands, UART0_BUFSIZE, uart0_readc, uart0_putc);
    shell_run(&shell);
}
