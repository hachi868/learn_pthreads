PROG := first_thread

CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread

SRCS =	first_thread.c

OBJS := $(SRCS:.c=.o)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

all: $(PROG)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(PROG)

re:	fclean all

.PHONY:	all clean fclean re
