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

void    ft_FreeTextureArray(t_TexArr *tex_arr)
{
    uint16_t    i = 0;

    while (i < tex_arr->len)
    {
        UnloadTexture(tex_arr->tex[i]);
        i++;
    }
    free(tex_arr->tex);
    free(tex_arr);
}

Texture2D   *ft_TexArrGet(t_TexArr *tex_arr, uint16_t id)
{
    if (id >= tex_arr->len)
        return (ft_Error("id provided is too high in ft_TexArrGet()"));
    return (&tex_arr->tex[id]);
}

void    ft_TexArrDraw(t_TexArr *tex_arr, uint16_t id,
    int x, int y, int w, int h, Vector2 origin, float rot)
{
    Texture2D   *curr = ft_TexArrGet(tex_arr, id);
    if (curr == NULL)
        return ;

    Rectangle   src = (Rectangle){0, 0, curr->width, curr->height};
    Rectangle   dst = (Rectangle){x, y, w, h};
    DrawTexturePro(*curr, src, dst, origin, rot, WHITE);
}

void    _ft_TexArrDrawDebug(t_TexArr *tex_arr)
{
    float scale = 40.0f;
    uint16_t i = 0;

    while (i < tex_arr->len)
    {
        ft_TexArrDraw(tex_arr, i,
                      i * scale, 0, scale, scale, (Vector2){0}, 0.0f);
        i++;
    }
}