#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
    int		len1;
    int		len2;
    char	*result;
    int		i;

    if (!s1)
        s1 = ft_strdup("");
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    result = (char *)malloc(sizeof(char) * ((len1 + len2) + 1));
    if (!result)
        return (NULL);
    i = -1;
    while (++i < len1)
        result[i] = s1[i];
    i = -1;
    while (++i < len2)
        result[len1 + i] = s2[i];
    result[len1 + len2] = '\0';
    return (result);
}