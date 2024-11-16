#include "libft.h"

char	*ft_copy_until(char *src, int n)
{
    char	*dest;
    int		i;

    dest = (char *)malloc(sizeof(char) * (n + 2));
    if (!dest)
        return (NULL);
    i = 0;
    while (i <= n)
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}