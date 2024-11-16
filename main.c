#include "fdf.h"

int    main(int argc, char **argv)
{
    fdf *data;

    data = (fdf*)malloc(sizeof(fdf));
    read_file(argv[1], data);

    int    i;
    int    j;

    i = 0;
    j = 0;
    while (i < data->height)
    {
        j = 0;
        while (j < data->width)
        {
              printf("%3d", data->z_matriz[i][j]);
              j++;
        }
        printf("\n");
        i++;
    }
    free(data);
}