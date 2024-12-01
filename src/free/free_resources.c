#include "../../fdf.h"

int	free_resources(t_fdf_gen *gen_data)
{
    // mlx_destroy_image(gen_data->data->mlx_ptr, gen_data->img_data->img_ptr);
    // mlx_destroy_window(gen_data->data->mlx_ptr, gen_data->data->win_ptr);
    // mlx_loop_end(gen_data->data->mlx_ptr);
    free(gen_data->graph);
    free(gen_data->mouse_set);
    free(gen_data->img_data);
    return(1);
}