#include "vars.h"

void    ft_GridTileInitSpawner(t_GridTile *tile)
{
    printf("Spawner tile created\n");
    tile->data = NULL;
    tile->fptr_update = NULL;
    tile->fptr_draw = NULL;
    tile->fptr_free_data = NULL;
}