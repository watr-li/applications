# name of your application
APPLICATION = chat

# If no BOARD is found in the environment, use this default:
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../RIOT

# Uncomment this to enable scheduler statistics for ps:
#CFLAGS += -DSCHEDSTATISTICS

# Uncomment this to enable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
CFLAGS += -DDEVELHELP #-DMICROCOAP_DEBUG

# Change this to 0 show compiler invocation lines by default:
export QUIET ?= 1

USEPKG=microcoap

# Modules to include:
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += uart0
USEMODULE += ps
USEMODULE += defaulttransceiver
USEMODULE += udp

include $(RIOTBASE)/Makefile.include
