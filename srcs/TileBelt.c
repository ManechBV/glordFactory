#include "vars.h"

void    ft_GridTileBeltDraw(void *param1_grid, void *param2_id)
{
    t_Grid  *grid = (t_Grid *) param1_grid;
    int     id = *((int*) param2_id);
    float   scale = grid->draw_scale;
    t_Tile  *curr;

    curr = grid->tiles[id];
    DrawTexturePro(*curr->tex_ptr,
                   (Rectangle){0, 0, curr->tex_ptr->width, curr->tex_ptr->height},
                   (Rectangle){
                    curr->pos_x * scale + scale / 2.0f, 
                    curr->pos_y * scale + scale / 2.0f,
                    scale, scale},
                   (Vector2){scale / 2.0f, scale / 2.0f}, 
                   ((t_TileBeltData*)curr->data)->rot, WHITE);
}

void    ft_GridTileBeltFreeData(void *data)
{
    t_TileBeltData  *belt_data = (t_TileBeltData*) data;

    printf("Belt data destroyed.\n");

    free(belt_data);
}

void    ft_GridTileBeltMouseRight(void *param1_grid, void *param2_data)
{
    t_Grid  *grid = (t_Grid*) param1_grid;
    t_TileBeltData  *curr_belt = (t_TileBeltData*) param2_data;

    curr_belt->rot += 90.0f;
    if (curr_belt->rot > 360.0f)
        curr_belt->rot -= 360.0f;
}

void    ft_GridTileBeltUpdate(void *param1_grid, void *param2_data)
{
    t_Grid  *grid = (t_Grid*) param1_grid;
    t_TileBeltData  *curr_belt = (t_TileBeltData*) param2_data;

}

int ft_GridTileSetBelt(t_Grid *grid, uint16_t id, float rot)
{
    t_TileBeltData  *belt_data;

    if (id > grid->len)
    {
        printf("Can't set tile data, id: %d too big.\n", id);
        return (1);
    }

    //  FREE PREVIOUS
    if (grid->tiles[id]->fptr_free_data != NULL)
        grid->tiles[id]->fptr_free_data(grid->tiles[id]->data);

    belt_data = malloc(sizeof(t_TileBeltData));
    if (!belt_data)
        return (1);
    belt_data->rot = rot;

    grid->tiles[id]->data = belt_data;
    _ft_GridSetTileType(grid, id, TILE_BELT);
    grid->tiles[id]->fptr_draw = &ft_GridTileBeltDraw;
    grid->tiles[id]->fptr_free_data = &ft_GridTileBeltFreeData;
    grid->tiles[id]->fptr_mouse_right = &ft_GridTileBeltMouseRight;
    grid->tiles[id]->fptr_update = &ft_GridTileBeltUpdate;

    return (0);
}
