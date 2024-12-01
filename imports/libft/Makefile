NAME=libft.a

CC = cc

FLAG = -Wall -Wextra -Werror

RM = rm -fr

#source files
SRC =				ft_atoi.c ft_split.c get_next_line.c \
					ft_strlen.c ft_copy_from.c ft_copy_until.c \
					ft_strdup.c ft_strjoin.c ft_wdcounter.c \
					ft_atoi_hexa.c	ft_strchr.c \
					ft_substr.c \
					ft_putstr.c

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