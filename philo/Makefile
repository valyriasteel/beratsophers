NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SRCS = philosophers.c \
		check_input.c \
		actions.c \
		time_scheduling.c \
		create_philo.c \
		threads.c \
		mutexes.c \
		
OBJS = $(SRCS:.c=.o)

RED = \x1b[31;01m
GREEN = \x1b[32;01m
BLUE = \033[34;1m
BOLD = \033[1m
RESET = \x1b[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "$(GREEN) Executable named philo created$(RESET)\n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@printf "$(BLUE) deleting object files$(RESET)\n"

fclean: clean
	@rm -rf $(NAME)
	@printf "$(RED) deleting executable name$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
