#include "vars.h"
#include <stdio.h>

t_Grid  *ft_Grid(uint16_t width, uint16_t height)
{
    t_Grid  *grid;

    if (width == 0 || height == 0)
        return (NULL);
    grid = malloc(sizeof(t_Grid));
    if (!grid)
        return (NULL);
    grid->draw_x = 0.0f;
    grid->draw_y = 0.0f;
    grid->draw_scale = 32.0f;
    grid->wid = width;
    grid->hei = height;
    grid->len = width * height;
    grid->textures = NULL;
    grid->nb_textures = 0;
    grid->tiles = NULL;
    grid->paint_type = TILE_EMPTY;
    return (grid);
}

void    ft_GridFree(t_Grid *grid)
{
    int i = 0;

    while (i < grid->len)
    {
        grid->tiles[i]->fptr_free_data(grid->tiles[i]->data);
        i++;
    }
    free(grid->tiles);
    free(grid->textures);
    free(grid);
}

int ft_GridLoadTextures(t_Grid *grid, char **paths)
{
    int         len;
    Texture2D   *textures;

    {
        int i = 0;

        while (paths[i] != NULL)
            i++;
        len = i;
    }
    if (len == 0)
        return (1);
    textures = malloc(sizeof(Texture2D) * len);
    if (!textures)
        return (1);
    grid->nb_textures = len;

    {
        int i = 0;

        while (i < len)
        {
            textures[i] = LoadTexture(paths[i]);
            i++;
        }
    }

    grid->textures = textures;
    return (0);
}

void    ft_GridUnloadTextures(t_Grid *grid)
{
    int i = 0;

    if (grid->textures == NULL)
        return ;
    while (i < grid->nb_textures)
    {
        UnloadTexture(grid->textures[i]);
        i++;
    }
}

void    ft_GridDrawPaintTile(t_Grid *grid)
{
    Texture2D   *tex_ptr = &(grid->textures[grid->paint_type]);
    DrawTexturePro(*tex_ptr,
                   (Rectangle){0, 0, tex_ptr->width, tex_ptr->height},
                   (Rectangle){0.0f, GetScreenHeight() - grid->draw_scale,
                                grid->draw_scale, grid->draw_scale},
                   (Vector2){0}, 0.0f, WHITE);
}