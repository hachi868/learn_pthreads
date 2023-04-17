PROG := prime_number

CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread

SRCS =	prime_number.c

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
