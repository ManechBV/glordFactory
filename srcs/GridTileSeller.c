#include "vars.h"

void    ft_GridTileInitSeller(t_GridTile *tile)
{
    printf("Seller tile created\n");
    tile->data = NULL;
    tile->fptr_update = NULL;
    tile->fptr_draw = NULL;
    tile->fptr_free_data = NULL;
}