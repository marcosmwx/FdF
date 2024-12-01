#include "../../fdf.h"

int	free_resources(t_fdf_gen *gen_data)
{
    free(gen_data->graph);
    free(gen_data->mouse_set);
    free(gen_data->img_data);
    return(1);
}