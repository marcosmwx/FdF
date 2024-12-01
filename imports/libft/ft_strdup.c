#include "libft.h"

char	*ft_strdup(const char *src)
{
    int		i;
    int		len;
    char	*dup;

    i = -1;
    if (!src)
        return (NULL);
    len = ft_strlen(src);
    dup = (char *)malloc(sizeof(char) * (len + 1));
    if (!dup)
        return (NULL);
    while (src[++i] != '\0')
        dup[i] = src[i];
    dup[len] = '\0';
    return (dup);
}