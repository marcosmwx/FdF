#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

typedef struct s_fdf
{
	int		width;
	int		height;
	int		**z_matriz;
	void	*mlx_ptr;
	void	*win_ptr;
}			t_fdf;

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

typedef struct s_color
{
	int		color;
	int		color_factor;
}			t_color;

void		read_file(char *file_name, t_fdf *data);
void		bresehnam(float x, float y, float x1, float y1, t_fdf *data,  t_graph *graph,  t_color *color_set,  t_img   *img_data);
void		draw(t_fdf *data,  t_graph *graph,  t_color *color_set,  t_img   *img_data);
int			mouse_move(int x, int y,t_fdf *data, t_graph *graph, t_color *color_set, t_mouse *mouse_set, t_img  *img_data);
int			mouse_press(int button, int x, int y, t_mouse *mouse_set);
int			mouse_release(int button, int x, int y, t_fdf *data);

#endif
