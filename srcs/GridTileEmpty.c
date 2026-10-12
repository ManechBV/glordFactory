#include "vars.h"

void    ft_GridTileInitEmpty(t_GridTile *tile)
{
    printf("Empty tile created\n");
    tile->data = NULL;
    tile->fptr_update = NULL;
    tile->fptr_draw = NULL;
    tile->fptr_free_data = NULL;
    tile->fptr_on_right_click = NULL;
}