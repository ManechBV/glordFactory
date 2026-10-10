#include "vars.h"

t_Grid  *ft_CreateGrid(uint16_t width, uint16_t height, t_TexArr *tex_arr)
{
    t_Grid  *grid;

    if (width == 0 || height == 0)
        return (ft_Error("width or height can't be 0 in ft_CreateGrid()"));

    grid = malloc(sizeof(t_Grid));
    if (!grid)
        return (ft_Error("Failed to malloc t_Grid in ft_CreateGrid"));
    
    grid->len = width * height;
    grid->wid = width;
    grid->hei = height;
    grid->tex_arr = tex_arr;
    grid->scale = 16.0f;
    grid->off_x = 0.0f;
    grid->off_y = 0.0f;
    grid->paint_type = GRIDTILE_BELT;

    grid->tiles = malloc(sizeof(t_GridTile) * grid->len);
    if (!(grid->tiles))
        return (ft_Error("Failed to malloc t_GridTile array in ft_CreateGrid"));

    t_GridTile  *curr;
    uint16_t    i = 0;
    while (i < grid->len)
    {
        curr = ft_GridGetTile(grid, i);
        if (curr == NULL)
            return (NULL);
        ft_GridSetTileType(grid, i, GRIDTILE_EMPTY);
        i++;
    }
    return (grid);
}

void    ft_FreeGrid(t_Grid *grid)
{
    ft_FreeTextureArray(grid->tex_arr);
    free(grid->tiles);
    free(grid);
}

void    ft_GridSetOffset(t_Grid *grid, float off_x, float off_y)
{
    grid->off_x = off_x;
    grid->off_y = off_y;
}

void    ft_GridIncreaseOffset(t_Grid *grid, float delta_x, float delta_y)
{
    grid->off_x += delta_x;
    grid->off_y += delta_y;
}

void    ft_GridSetScale(t_Grid *grid, float scale)
{
    if (scale < 1.0f)
    {
        ft_Error("Can't set scale to value lower than 1.0f in ft_GridSetScale()");
        return ;
    }
    grid->scale = scale;
}

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

void    ft_GridDraw(t_Grid *grid)
{
    uint16_t    i = 0;
    uint16_t    x = 0;
    uint16_t    y = 0;
    t_GridTile  *curr;

    while (i < grid->len)
    {
        curr = ft_GridGetTile(grid, i);
        if (curr == NULL)
            return ;
        ft_GridGetTileCoord(grid, i, &x, &y);
        ft_TexArrDraw(grid->tex_arr, curr->type,
            grid->off_x + (x * grid->scale),
            grid->off_y + (y * grid->scale),
            grid->scale, grid->scale,
            (Vector2){0}, 0.0f);
        i++;
    }
}