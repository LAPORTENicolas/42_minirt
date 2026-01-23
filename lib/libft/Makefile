
CC = cc
CFLAGS = -Wall -Werror -Wextra -fPIC
NAME = libft.a
INCLUDES = libft.h
SRCS = ft_atoi.c ft_atof.c ft_isascii.c ft_memcpy.c ft_putnbr_fd.c ft_striteri.c ft_strmapi.c ft_substr.c ft_bzero.c ft_isdigit.c ft_memmove.c ft_putstr_fd.c \
       ft_strjoin.c ft_strncmp.c ft_tolower.c ft_calloc.c ft_isprint.c ft_memset.c ft_split.c ft_strlcat.c ft_strnstr.c ft_toupper.c ft_isalnum.c \
       ft_itoa.c ft_memchr.c ft_putchar_fd.c ft_strchr.c ft_strlcpy.c ft_strrchr.c ft_isalpha.c ft_memcmp.c ft_putendl_fd.c ft_strdup.c ft_strlen.c \
       ft_strtrim.c ft_atol.c ft_isspace.c ft_strjoin_free.c ft_strndup.c ft_isnumber.c ft_strcmp.c ft_lstadd_front_bonus.c ft_lstmap_bonus.c \
	   ft_lstclear_bonus.c ft_lstnew_bonus.c ft_lstdelone_bonus.c ft_lstsize_bonus.c ft_lstiter_bonus.c \
	   ft_lstadd_back_bonus.c ft_lstlast_bonus.c  ft_free_split.c

OBJS = $(SRCS:.c=.o)
      
all: $(NAME)

re : clean all

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "libft compilée ✔️"

%.o: %.c $(INCLUDES)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -f $(OBJS)

fclean : clean
	@rm -f $(NAME)

.PHONY: clean all re fclean


