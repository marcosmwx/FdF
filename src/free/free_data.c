#include "../../fdf.h"

void free_data(t_fdf *data)
{
    int i;
    int j;

    if (!(data))
        return ;
    if ((data)->z_matriz)
    {
        i = 0;
        while (i < (data)->height)
        {
            j = 0;
            while (j < (data)->width)
            {
                if ((data)->z_matriz[i][j].hex)
                    free((data)->z_matriz[i][j].hex); // Libera a string hex
                j++;
            }
            free((data)->z_matriz[i]); // Libera a linha da matriz
            i++;
        }
        free((data)->z_matriz); // Libera o ponteiro da matriz
    }
    free(data); // Libera a estrutura principal
    data = NULL;
}