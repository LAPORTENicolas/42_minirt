SRCS 	= get_next_line.c get_next_line_bonus.c get_next_line_utils.c get_next_line_utils_bonus.c
OBJS 	= $(SRCS:.c=.o)
NAME 	= libgnl.a
CC 		= cc

%.o: %.c
	$(CC) -Wall -Werror -Wextra -c $< -o $@

NAME: $(OBJS)
	@ar crs ${NAME} ${OBJS}

clean: 
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)
