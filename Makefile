NAME=	fdf

IMPORTS=	imports/
LIBFT_PATH=	$(IMPORTS)libft/
MINILIB_PATH= $(IMPORTS)minilibx-linux/

LIBFT_A=	$(LIBFT_PATH)libft.a
MINILIB_A= 	$(MINILIB_PATH)libmlx.a

CC=		cc
CFLAGS=	-g -Wall -Werror -Wextra
INCLUDE= includes

SRCS=	main.c \
		src/free/free_data.c \
		src/free/free_resources.c \
		src/free/clear_image.c \
		src/key/key_hook.c \
		src/key/mouse_control.c \
		src/map/read_file.c \
		src/map/read_file_utils.c \
		src/graph/draw_trace_lines.c \
		src/graph/draw_utils.c \
		src/graph/draw.c



OBJS=	$(SRCS:.c=.o)

all: $(LIBFT_A) $(NAME)
#$(MINILIB_A) add after

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L $(LIBFT_PATH) -lft -L $(MINILIB_PATH) -lmlx -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

#$(MINILIB_A):
#	@make -C $(MINILIB_PATH)

#$(LIBFT_A):
#	@make -C $(LIBFT_PATH)

clean:
	@rm -f $(OBJS)

fclean: clean
	@make clean -C $(LIBFT_PATH)
	#@make clean -C $(MINILIB_PATH)
	@rm -rf $(NAME)

r: $(NAME)
	@clear
	@./$(NAME) ./mwx.fdf

c: fclean $(NAME)