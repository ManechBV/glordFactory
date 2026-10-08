#include "vars.h"

void    ft_GridTileSellerDraw(void *param1_grid, void *param2_id)
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
                   ((t_TileSellerData*)curr->data)->rot, WHITE);
}

void    ft_GridTileSellerFreeData(void *data)
{
    t_TileSellerData  *belt_data = (t_TileSellerData*) data;

    printf("Seller data destroyed.\n");

    free(belt_data);
}

void    ft_GridTileSellerMouseRight(void *param1_grid, void *param2_data)
{
    t_Grid  *grid = (t_Grid*) param1_grid;
    t_TileSellerData  *curr_seller = (t_TileSellerData*) param2_data;

    curr_seller->rot += 90.0f;
    if (curr_seller->rot > 360.0f)
        curr_seller->rot -= 360.0f;
}

void    ft_GridTileSellerUpdate(void *param1_grid, void *param2_data)
{
    t_Grid  *grid = (t_Grid*) param1_grid;
    t_TileSellerData  *curr_seller = (t_TileSellerData*) param2_data;
}

int ft_GridTileSetSeller(t_Grid *grid, uint16_t id, float rot)
{
    t_TileSellerData  *belt_data;

    if (id > grid->len)
    {
        printf("Can't set tile data, id: %d too big.\n", id);
        return (1);
    }

    //  FREE PREVIOUS
    if (grid->tiles[id]->fptr_free_data != NULL)
        grid->tiles[id]->fptr_free_data(grid->tiles[id]->data);

    belt_data = malloc(sizeof(t_TileSellerData));
    if (!belt_data)
        return (1);
    belt_data->rot = rot;

    grid->tiles[id]->data = belt_data;
    _ft_GridSetTileType(grid, id, TILE_SELLER);
    grid->tiles[id]->fptr_draw = &ft_GridTileSellerDraw;
    grid->tiles[id]->fptr_free_data = &ft_GridTileSellerFreeData;
    grid->tiles[id]->fptr_mouse_right = &ft_GridTileSellerMouseRight;
    grid->tiles[id]->fptr_update = &ft_GridTileSellerUpdate;

    return (0);
}
