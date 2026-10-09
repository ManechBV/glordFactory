#include "vars.h"

void    ft_GridHandleInput(t_Grid *Grid)
{
        if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
        {
            Grid->paint_type++;
            if (Grid->paint_type > TILE_SPAWNER)
                Grid->paint_type = TILE_EMPTY;
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            uint16_t    map_x = GetMouseX() / Grid->draw_scale;
            uint16_t    map_y = GetMouseY() / Grid->draw_scale;
            printf("map_x: %d map_y: %d\n", map_x, map_y);
            uint16_t    id = (map_y * Grid->wid) + map_x;

            if (Grid->paint_type == TILE_EMPTY)
                ft_GridTileSetEmpty(Grid, id);
            else if (Grid->paint_type == TILE_BELT)
                ft_GridTileSetBelt(Grid, id, 0.0f);
            else if (Grid->paint_type == TILE_SELLER)
                ft_GridTileSetSeller(Grid, id, 0.0f);
            else if (Grid->paint_type == TILE_SPAWNER)
                ft_GridTileSetSpawner(Grid, id, 0.0f);
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            uint16_t    map_x = GetMouseX() / Grid->draw_scale;
            uint16_t    map_y = GetMouseY() / Grid->draw_scale;
            uint16_t    id = (map_y * Grid->wid) + map_x;

            Grid->tiles[id]->fptr_mouse_right(Grid, Grid->tiles[id]->data);
        }
}

int main(void)
{
    InitWindow(1280, 720, "Glorb Factory");

    t_Vars  Vars;

    Vars.grid = ft_Grid(20, 20);
    if (!Vars.grid)
    {
        CloseWindow();
        return (1);
    }

    char    *textures_paths[] = {
        "res/empty_tile.png",
        "res/belt_tile.png", 
        "res/seller_tile.png", 
        "res/spawner_tile.png", 
        NULL
    };
    if (ft_GridLoadTextures(Vars.grid, textures_paths) != 0)
        return (1);
    
    if (ft_GridGenerateTiles(Vars.grid) != 0)
        return (1);

    while (!WindowShouldClose())
    {
        ft_GridHandleInput(Vars.grid);
        ft_GridUpdateTiles(Vars.grid);

        BeginDrawing();
            ClearBackground(BLACK);
            ft_GridDrawTiles(Vars.grid);
            ft_GridDrawPaintTile(Vars.grid);
        EndDrawing();
    }

    ft_GridUnloadTextures(Vars.grid);
    ft_GridFree(Vars.grid);

    CloseWindow();

    return 0;
}