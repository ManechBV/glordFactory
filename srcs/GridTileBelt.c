#include "vars.h"

static void    ft_GridTileFreeBelt(t_GridTile *self)
{
    free(self->data);
}

static void     ft_GridTileBeltOnRightClick(t_GridTile *self)
{
    t_GridTileBelt  *belt = (t_GridTileBelt*) self->data;

    belt->rot += 90.0f;
    if (belt->rot >= 360.0f)
        belt->rot = 0.0f;
}

static void     ft_GridTileBeltDraw(t_GridTile *self, void *data_grid, uint16_t i)
{
    t_GridTileBelt  *belt = (t_GridTileBelt*) self->data;
    t_Grid          *grid = (t_Grid *) data_grid;
    uint16_t        x = 0;
    uint16_t        y = 0;

    ft_GridGetTileCoord(grid, i, &x, &y);
    ft_TexArrDraw(grid->tex_arr, self->type,
                  grid->off_x + (x * grid->scale) + (grid->scale / 2.0f),
                  grid->off_y + (y * grid->scale) + (grid->scale / 2.0f),
                  grid->scale, grid->scale,
                  (Vector2){grid->scale / 2.0f, grid->scale / 2.0f}, belt->rot);
}

void    ft_GridTileInitBelt(t_GridTile *tile)
{
    t_GridTileBelt  *belt;

    belt = malloc(sizeof(t_GridTileBelt));
    if (!belt)
    {
        ft_Error("NOONONNON BELT PA PU CRERRERE");
        return ;
    }

    printf("Belt tile created\n");

    belt->rot = 0.0f;
    tile->data = belt;
    tile->fptr_update = NULL;
    tile->fptr_draw = ft_GridTileBeltDraw;
    tile->fptr_free_data = ft_GridTileFreeBelt;
    tile->fptr_on_right_click = ft_GridTileBeltOnRightClick;
}