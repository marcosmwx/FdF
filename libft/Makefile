NAME=libft.a

CC = cc

FLAG = -Wall -Wextra -Werror

RM = rm -fr

#source files
SRC =				ft_atoi.c ft_split.c get_next_line.c \
					ft_strlen.c ft_copy_from.c ft_copy_until.c \
					ft_strdup.c ft_strjoin.c
					#ft_isalnum.c ft_isprint.c ft_memcmp.c \
					ft_strlcat.c ft_strncmp.c ft_substr.c \
					ft_atoi.c ft_isalpha.c ft_memcpy.c \
					ft_strchr.c  ft_strlcpy.c ft_strnstr.c ft_tolower.c \
					ft_isascii.c ft_memmove.c ft_strdup.c \
					ft_strlen.c  ft_strrchr.c ft_toupper.c \
					ft_calloc.c  ft_isdigit.c ft_memchr.c \
					ft_memset.c ft_strjoin.c ft_strmapi.c \
					ft_itoa.c ft_strtrim.c ft_striteri.c \
					ft_putchar_fd.c ft_putstr_fd.c ft_bzero.c \
					ft_putendl_fd.c ft_putnbr_fd.c ft_split.c

OBJS = $(SRC:.c=.o)

$(NAME) : $(OBJS)
	ar -rc $(NAME) $(OBJS)

.c.o:
	$(CC) $(FLAG) -c $< -o $(<:.c=.o)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re