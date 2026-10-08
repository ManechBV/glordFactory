#include "vars.h"

void    ft_GridTileEmptyDraw(void *param1_grid, void *param2_id)
{
    t_Grid  *grid = (t_Grid *) param1_grid;
    int     id = *((int*) param2_id);
    float   scale = grid->draw_scale;
    t_Tile  *curr;

    curr = grid->tiles[id];
    DrawTexturePro(*(curr->tex_ptr),
                   (Rectangle){0, 0, curr->tex_ptr->width, curr->tex_ptr->height},
                   (Rectangle){curr->pos_x * scale, curr->pos_y * scale, scale, scale},
                   (Vector2){0}, 0.0f, WHITE);
}

void    ft_GridTileEmtpyMouseRight(void *param1_grid, void *param2_data)
{

}

void ft_GridTileEmptyFreeData(void *data)
{
    // its empty, nothing to free
    printf("Empty data destroyed.\n");
}

int ft_GridTileSetEmpty(t_Grid *grid, uint16_t id)
{
    if (id > grid->len)
    {
        printf("Can't set tile data, id: %d too big.\n", id);
        return (1);
    }

    //  FREE PREVIOUS
    if (grid->tiles[id]->fptr_free_data != NULL)
        grid->tiles[id]->fptr_free_data(grid->tiles[id]->data);

    grid->tiles[id]->data = NULL;
    _ft_GridSetTileType(grid, id, TILE_EMPTY);
    grid->tiles[id]->fptr_draw = &ft_GridTileEmptyDraw;
    grid->tiles[id]->fptr_free_data = &ft_GridTileEmptyFreeData;
    grid->tiles[id]->fptr_mouse_right = &ft_GridTileEmtpyMouseRight;

    return (0);
}