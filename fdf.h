/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malopes- <malopes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:25:11 by malopes-          #+#    #+#             */
/*   Updated: 2024/12/01 20:25:11 by malopes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "imports/libft/libft.h"
# include "imports/minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# define NF_MAP "Can't execute the program, the context dont have a map file"

typedef struct s_point
{
	int		value;
	char	*hex;
}	t_point;

typedef struct s_fdf
{
	int		width;
	int		win_width;
	int		height;
	int		win_height;
	void	*mlx_ptr;
	void	*win_ptr;
	t_point	*z_matrix;
}	t_fdf;

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
	int		click_active;
}			t_mouse;

typedef struct s_img
{
	int		bpp;
	int		size_line;
	int		endian;
	void	*img_ptr;
	char	*img_data;
}		t_img;

typedef struct s_coords
{
    float x;
    float y;
    float x1;
    float y1;
    int z;
    int z1;
    int start_color;
} t_coords;

typedef struct s_fdf_gen
{
	t_fdf	*data;
	t_graph	*graph;
	t_img	*img_data;
	t_mouse	*mouse_set;
}		t_fdf_gen;


int			read_file(char *file_name, t_fdf *data);
int			mouse_move(int x, int y, t_fdf_gen *gen_data);
int			mouse_press(int button, int x, int y, t_fdf_gen *gen_data);
int			free_resources(t_fdf_gen *gen_data);
int			key_hook(int keycode, t_fdf_gen *gen_data);
int			check_line_width_consistency(int fd, int width);
int			get_height(char *file_name);
int			get_width(char *file_name);
int			free_pointer_server(t_fdf_gen *gen_data);
int			mouse_move_event(int x, int y, void *param);
int			set_mouse_up(int button, int x, int y, void *param);
int			set_mouse_down(int button, int x, int y, void *param);
void		free_data(t_fdf *data);
void		draw(t_fdf_gen *gen_data);
void		clear_image(t_fdf *data, t_img *img_data);
void		trace_lines(float *x_step, float *y_step, t_coords *coords, t_fdf_gen *gen_data);
void		get_initial_values(t_coords *coords, t_fdf *data);
void		apply_scale_zoom(t_coords *coords, t_graph *graph);
void		apply_center_of_map(t_coords *coords, t_fdf_gen *gen_data);
void		apply_shift(t_coords *coords, t_graph *graph);
void		pack_hooks(t_fdf_gen *gen_data);
#endif
