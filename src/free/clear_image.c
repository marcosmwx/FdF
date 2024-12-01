#include "../../fdf.h"

void	clear_image(t_fdf *data, t_img *img_data)
{
    mlx_destroy_image(data->mlx_ptr, img_data->img_ptr);
    img_data->img_ptr = mlx_new_image(data->mlx_ptr, data->win_width, data->win_height);
    img_data->img_data = mlx_get_data_addr(img_data->img_ptr, &img_data->bpp, &img_data->size_line, &img_data->endian);
}