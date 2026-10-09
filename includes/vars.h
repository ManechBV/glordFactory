#ifndef VARS_H
# define VARS_H

# include "raylib.h"
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>

typedef enum
{
    TILE_EMPTY,
    TILE_BELT,
    TILE_SELLER,
    TILE_SPAWNER
}   e_TileType;

typedef struct  s_TileBeltData
{
    float   rot;
}   t_TileBeltData;

typedef struct  s_TileSellerData
{
    float   rot;
}   t_TileSellerData;

typedef struct  s_TileSpawnerData
{
    float   rot;
}   t_TileSpawnerData;

typedef struct  s_Tile
{
    void        *data;
    void        (*fptr_draw)(void *param1_grid, void *param2_id);
    void        (*fptr_free_data)(void *data);
    void        (*fptr_mouse_right)(void *param1_grid, void *param2_data);
    void        (*fptr_update)(void *param1_grid, void *param2_data);
    uint16_t    id;
    uint16_t    pos_x;
    uint16_t    pos_y;
    Texture2D   *tex_ptr;
    e_TileType  type;
}   t_Tile;

typedef struct  s_Grid
{
    t_Tile      **tiles;
    float       draw_x;
    float       draw_y;
    float       draw_scale;
    uint16_t    wid;
    uint16_t    hei;
    uint16_t    len;
    Texture2D   *textures;
    uint16_t    nb_textures;
    e_TileType  paint_type;
}   t_Grid;

typedef struct  s_Vars
{
    t_Grid  *grid;
}   t_Vars;

//  Grid.c
t_Grid  *ft_Grid(uint16_t width, uint16_t height);
int     ft_GridLoadTextures(t_Grid *grid, char **paths);
void    ft_GridUnloadTextures(t_Grid *grid);
void    ft_GridFree(t_Grid *grid);
void    ft_GridDrawPaintTile(t_Grid *grid);

//  Tile.c
void    _ft_GridSetTileType(t_Grid *grid, uint16_t id, e_TileType type);
int     ft_GridGenerateTiles(t_Grid *grid);
void    ft_GridDrawTiles(t_Grid *grid);
int     ft_GridTileSetBelt(t_Grid *grid, uint16_t id, float rot);
void    ft_GridUpdateTiles(t_Grid *grid);

//  TileBelt.c
int     ft_GridTileSetBelt(t_Grid *grid, uint16_t id, float rot);
int     ft_GridTileSetEmpty(t_Grid *grid, uint16_t id);

//  TileBelt.c
int     ft_GridTileSetSeller(t_Grid *grid, uint16_t id, float rot);

//  TileSpawner.c
int     ft_GridTileSetSpawner(t_Grid *grid, uint16_t id, float rot);

#endif