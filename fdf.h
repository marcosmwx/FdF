#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <fcntl.h>

#  define WIN_WIDTH 920
#  define WIN_HEIGHT 760

typedef struct s_point
{
	int value;      // Valor Z
	char *hex;      // Cor em formato de string (char *)
} t_point;

typedef struct s_fdf
{
	int        width;
	int        height;
	t_point    **z_matriz; // Matriz contendo cor e valor
	void       *mlx_ptr;
	void       *win_ptr;
} t_fdf;

typedef struct s_graph
{
	int		zoom;
	int		shift_x;
	int		shift_y;
	float	angle_x;
	float	angle_y;
	float	depth_factor;
}			t_graph;

typedef struct s_mouse
{
	int		last_mouse_x;
	int		last_mouse_y;
	int		mouse_pressed;
}			t_mouse;

typedef struct s_img
{
	void *img_ptr;  // Adicionado para a imagem
	char *img_data; // Dados da imagem
	int bpp;        // Bytes por pixel
	int size_line;  // Tamanho da linha
	int endian;     // Endianness
}			t_img;

typedef struct s_fdf_gen {
    t_fdf *data;
    t_graph *graph;
    t_img *img_data;
	t_mouse *mouse_set;
}			t_fdf_gen;

int			read_file(char *file_name, t_fdf *data);
void		bresehnam(float x, float y, float x1, float y1, t_fdf *data,  t_graph *graph, t_img   *img_data);
void		draw(t_fdf *data,  t_graph *graph,  t_img *img_data);
int			mouse_move(int x, int y, t_fdf_gen *gen_data);
int			mouse_press(int button, int x, int y, t_fdf_gen *gen_data);
int			free_resources(t_fdf_gen *gen_data);
void		free_data(t_fdf *data);
int			key_hook(int keycode, t_fdf_gen *gen_data);

#endif
