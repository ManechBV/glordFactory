#include "vars.h"

void    *ft_Error(char *msg)
{
    printf("%s\n", msg);
    return (NULL);
}

int     ft_ErrorInt(char *msg, int ret)
{
    printf("%s\n", msg);
    return (ret);
}