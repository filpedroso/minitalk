##### MAKEFILE FOR MINITALK #####

# Colors
BLACK		= \033[1;30m
RED			= \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
MAGENTA		= \033[1;35m
CYAN		= \033[1;36m
WHITE		= \033[1;37m
NC			= \033[0m # No Color

# Compilation Variables
CLI = client
SER = server
CC = cc
CFLAGS = -g -Wextra -Wall -Werror
SRC = $(MANDATORY)
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a

# Verbose flag
VB	= 0

# Check if VERBOSE is set to 1
ifeq ($(VB),1)
	AT =
else
	AT = @
endif


MANDATORY = \
	client.c \
	server.c

all: $(LIBFT) $(CLI) $(SER)

%.o: %.c
	$(AT) $(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@printf "$(WHITE)Compiling libft: |"
	$(AT) $(MAKE) -C libft | awk '{printf "="; fflush()}'
	@printf "|\n"
	@printf "$(BLUE)LIBFT compiled.\n"

$(CLI): $(OBJ) $(LIBFT)
	$(AT) $(CC) $(CFLAGS) client.o $(LIBFT) -o $(CLI)
	@printf "$(CYAN)client compiled.\n"

$(SER): $(OBJ) $(LIBFT)
	$(AT) $(CC) $(CFLAGS) server.o $(LIBFT) -o $(SER)
	@printf "$(GREEN)server compiled.\n"



clean:
	$(AT) $(MAKE) -C libft clean | awk {}
	@printf "$(WHITE)LIBFT objects deleted.\n"
	$(AT) rm -f $(OBJ)
	@printf "$(BLACK)Object files deleted.\n"

fclean: clean
	$(AT) $(MAKE) -C libft fclean | awk {}
	$(AT) rm -f $(CLI) $(SER)
	@printf "$(RED)Client and Server executables deleted.\n"

re: fclean all

.PHONY: all clean fclean re
