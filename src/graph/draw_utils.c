#include "../../fdf.h"

void	get_initial_values(int *z, int *z1, int *start_color, float x, float x1, float y, float y1, t_fdf *data)
{
		// get z values inside blocks of matrix - initial values
	*z = data->z_matrix[(int)y][(int)x].value;
	*z1 = data->z_matrix[(int)y1][(int)x1].value;
	*start_color = ft_atoi_hexa(data->z_matrix[(int)y][(int)x].hex);
}

void	apply_scale_zoom(float *x, float *y, float *x1, float *y1, t_graph *graph)
{
	//apply scale of zoom of any original value of scale
	*x *= graph->zoom;
	*y *= graph->zoom;
	*x1 *= graph->zoom;
	*y1 *= graph->zoom;
}

void	apply_center_of_map(float *x, float *y, float *x1, float *y1, t_fdf *data, t_graph *graph)
{
	//before any change we turn the view a center of map
	*x -= (data->width - 1) * graph->zoom / 2.0;
	*y -= (data->height - 1) * graph->zoom / 2.0;
	*x1 -= (data->width - 1) * graph->zoom / 2.0;
	*y1 -= (data->height - 1) * graph->zoom / 2.0;
}

void	apply_shift(float *x, float *y, float *x1, float *y1, t_graph *graph)
{
	// apply shift for render on center of view after change scale
	*x += graph->shift_x;
	*y += graph->shift_y;
	*x1 += graph->shift_x;
	*y1 += graph->shift_y;
}