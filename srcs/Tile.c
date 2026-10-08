#include "vars.h"
#include <stdio.h>

t_Tile  *ft_Tile(uint16_t id)
{
    t_Tile  *tile;

    tile = malloc(sizeof(t_Tile));
    if (!tile)
        return (NULL);
    tile->id = id;
    tile->pos_x = 0;
    tile->pos_y = 0;
    tile->type = TILE_EMPTY;
    tile->tex_ptr = NULL;
    tile->fptr_draw = NULL;
    tile->fptr_free_data = NULL;
    tile->fptr_mouse_right = NULL;
    tile->fptr_update = NULL;
    tile->data = NULL;
    return (tile);
}

void    _ft_GridSetTileType(t_Grid *grid, uint16_t id, e_TileType type)
{
    if (id >= grid->len || type >= grid->nb_textures)
    {
        printf("Failed to change tile type, maybe no texture for this ?\n");
        return ;
    }
    grid->tiles[id]->type = type;
    grid->tiles[id]->tex_ptr = &grid->textures[type];
}

int ft_GridGenerateTiles(t_Grid *grid)
{
    grid->tiles = malloc(sizeof(t_Tile *) * grid->len);
    if (!(grid->tiles))
        return (1);
    
    {
        int i = 0;

        while (i < grid->len)
        {
            grid->tiles[i] = ft_Tile(i);
            if (!(grid->tiles[i]))
                return (1);
            grid->tiles[i]->pos_x = i % grid->wid;
            grid->tiles[i]->pos_y = i / grid->wid;
            ft_GridTileSetEmpty(grid, i);
            i++;
        }
    }
    return (0);
}

void    ft_GridDrawTiles(t_Grid *grid)
{
    int     i = 0;

    while (i < grid->len)
    {
        grid->tiles[i]->fptr_draw(grid, &i);
        i++;
    }
}

void    ft_GridUpdateTiles(t_Grid *grid)
{
    uint16_t    i = 0;
    t_Tile      *curr;

    while (i < grid->len)
    {
        curr = grid->tiles[i];
        if (curr->type == TILE_EMPTY)
        {
            i++;
            continue;
        }
        curr->fptr_update(grid, curr->data);
        i++;
    }
}

/*
void    ft_GridDrawTiles(t_Grid *grid)
{
    float   scale = grid->draw_scale;
    int     i = 0;
    t_Tile  *curr;

    while (i < grid->len)
    {
        curr = grid->tiles[i];
        DrawTexturePro(*curr->tex_ptr,
            (Rectangle){0, 0, curr->tex_ptr->width, curr->tex_ptr->height},
            (Rectangle){curr->pos_x * scale, curr->pos_y * scale, scale, scale},
            (Vector2){0}, 0.0f, WHITE);
        i++;
    }
}
*/