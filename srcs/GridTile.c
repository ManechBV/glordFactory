#include "vars.h"

void    ft_GridSetTileType(t_Grid *grid, uint16_t id, e_GridTileType type)
{
    t_GridTile  *tile;

    tile = ft_GridGetTile(grid, id);
    if (tile == NULL)
        return ;
    if (tile->fptr_free_data != NULL)
        (tile->fptr_free_data)(tile);
    tile->type = type;
    //  G_fptrarr_GridTileInits cié un tablo de poingteur de fonqusions pour init les bails
    (G_fptrarr_GridTileInits[type])(tile);
}

void    ft_GridPaintTileAtMouse(t_Grid *grid)
{
    float       x = GetMouseX() - grid->off_x;
    float       y = GetMouseY() - grid->off_y;
    uint16_t    map_x = x / grid->scale;
    uint16_t    map_y = y / grid->scale;
    uint16_t    id  = (map_y * grid->wid) + map_x;

    if (map_x >= grid->wid || map_y >= grid->hei)
    {
        ft_Error("Tried to paint but not on tiles, goo goo ga ga?");
        return ;
    }
    ft_GridSetTileType(grid, id, grid->paint_type);
}

void    ft_GridTileRightClick(t_Grid *grid)
{
    float       x = GetMouseX() - grid->off_x;
    float       y = GetMouseY() - grid->off_y;
    uint16_t    map_x = x / grid->scale;
    uint16_t    map_y = y / grid->scale;
    uint16_t    id  = (map_y * grid->wid) + map_x;

    if (map_x >= grid->wid || map_y >= grid->hei)
    {
        ft_Error("Tried to paint but not on tiles, goo goo ga ga?");
        return ;
    }
    if (grid->tiles[id].fptr_on_right_click != NULL)
        grid->tiles[id].fptr_on_right_click(&(grid->tiles[id]));
}

t_GridTile  *ft_GridGetTile(t_Grid *grid, uint16_t id)
{
    if (id >= grid->len)
        return (ft_Error("id too big, no tile corresponding in ft_GridGetTile"));
    return (&grid->tiles[id]);
}

void    ft_GridGetTileCoord(t_Grid *grid, uint16_t id, uint16_t *x, uint16_t *y)
{
    if (id >= grid->len)
    {
        ft_Error("id too big, no tile corresponding in ft_GridGetTileCoord()");
        return ;
    }
    *x = id % grid->wid;
    *y = id / grid->wid;
}