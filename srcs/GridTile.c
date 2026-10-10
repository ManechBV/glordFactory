#include "vars.h"

void    ft_GridSetTileType(t_Grid *grid, uint16_t id, e_GridTileType type)
{
    t_GridTile  *tile;

    tile = ft_GridGetTile(grid, id);
    if (tile == NULL)
    {
        ft_Error("Can't set type to tile, id too big in ft_GridSetTileType()");
        return ;
    }
    tile->type = type;
}

void    ft_GridPaintTileAtMouse(t_Grid *grid)
{
    float       x = GetMouseX() - grid->off_x;
    float       y = GetMouseY() - grid->off_y;
    uint16_t    map_x = x / grid->scale;
    uint16_t    map_y = y / grid->scale;
    uint16_t    id  = (map_y * grid->wid) + map_x;

    ft_GridSetTileType(grid, id, grid->paint_type);
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
