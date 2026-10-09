#include "vars.h"

t_TexArr    *ft_CreateTextureArray(uint16_t ac, char **av)
{
    t_TexArr    *tex_arr;

    if (ac == 0)
        return (ft_Error("ac can't be 0 in ft_CreateTextureArray()"));

    tex_arr = malloc(sizeof(t_TexArr));
    if (!tex_arr)
        return (ft_Error("Failed to malloc t_TexArr in ft_CreateTextureArray()"));

    tex_arr->len = ac;
    tex_arr->tex = malloc(sizeof(Texture2D) * ac);
    if (!(tex_arr->tex))
        return (ft_Error("Failed to malloc t_TexArr.tex in ft_CreateTextureArray()"));
    
    uint16_t    i = 0;

    while (i < ac)
    {
        tex_arr->tex[i] = LoadTexture(av[i]);
        i++;
    }
    return (tex_arr);
}

Texture2D   *ft_TexArrGet(t_TexArr *tex_arr, uint16_t id)
{
    if (id >= tex_arr->len)
        return (ft_Error("id provided is too high in ft_TexArrGet()"));
    return (&tex_arr->tex[id]);
}