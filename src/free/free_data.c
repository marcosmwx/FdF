#include "../../fdf.h"

void free_data(t_fdf *data)
{
    int i;
    int j;

    if (!(data))
        return ;
    if ((data)->z_matrix)
    {
        i = 0;
        while (i < (data)->height)
        {
            j = 0;
            while (j < (data)->width)
            {
                if ((data)->z_matrix[i][j].hex)
                    free((data)->z_matrix[i][j].hex); // Libera a string hex
                j++;
            }
            free((data)->z_matrix[i]); // Libera a linha da matrix
            i++;
        }
        free((data)->z_matrix); // Libera o ponteiro da matrix
    }
    free(data); // Libera a estrutura principal
    data = NULL;
}
