#ifndef VARS_H
# define VARS_H

# include "raylib.h"
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>

//  - - - - ERROR MANAGMENT DATA    - - - -
//  ft_Error.c
void    *ft_Error(char *msg);
int     ft_ErrorInt(char *msg, int ret);


//  - - - - TEXTURE ARRAY DATA      - - - -
typedef struct  s_TexArr
{
    uint16_t    len;
    Texture2D   *tex;
}   t_TexArr;

//  TextureArray.c
t_TexArr    *ft_CreateTextureArray(uint16_t ac, char **av);
void        ft_FreeTextureArray(t_TexArr *tex_arr);

Texture2D   *ft_TexArrGet(t_TexArr *tex_arr, uint16_t id);

void        _ft_TexArrDrawDebug(t_TexArr *tex_arr);
void        ft_TexArrDraw(t_TexArr *tex_arr, uint16_t id,
                   int x, int y, int w, int h, Vector2 origin, float rot);


//  - - - - GRID DATA               - - - -
typedef enum
{
    GRIDTILE_EMPTY,
    GRIDTILE_BELT,
    GRIDTILE_SELLER,
    GRIDTILE_SPAWNER
}   e_GridTileType;

typedef struct  s_GridTile
{
    e_GridTileType  type;
}   t_GridTile;

typedef struct  s_Grid
{
    t_GridTile      *tiles;
    t_TexArr        *tex_arr;
    uint16_t        len;
    uint16_t        wid;
    uint16_t        hei;
    float           scale;
    float           off_x;
    float           off_y;
    e_GridTileType  paint_type;
}   t_Grid;

//  Grid.c
t_Grid      *ft_CreateGrid(uint16_t width, uint16_t height, t_TexArr *tex_arr);
void        ft_FreeGrid(t_Grid *grid);

t_GridTile  *ft_GridGetTile(t_Grid *grid, uint16_t id);
void        ft_GridSetTileType(t_Grid *grid, uint16_t id, e_GridTileType type);
void        ft_GridSetOffset(t_Grid *grid, float off_x, float off_y);
void        ft_GridSetScale(t_Grid *grid, float scale);
void        ft_GridIncreaseOffset(t_Grid *grid, float delta_x, float delta_y);

void        ft_GridPaintTileAtMouse(t_Grid *grid);

void        ft_GridDraw(t_Grid *grid);


//  - - - - USER INTERFACE DATA     - - - -
typedef struct  s_UserInterfaceButton
{
    float       x;
    float       y;
    float       w;
    float       h;
    Texture2D   *tex_ptr;
    Color       color;
    void        *data;
    void        (*fptr_pressed)(struct s_UserInterfaceButton *self, void *data_vars);
    struct s_UserInterfaceButton    *next;
}   t_UserInterfaceButton;

typedef struct  s_UserInterface
{
    t_UserInterfaceButton   *buttons_lst;
    uint16_t                len;
    bool                    hidden;
}   t_UserInterface;

//  UserInterface.c
t_UserInterface         *ft_CreateUserInterface(void);
void                    ft_FreeUserInterface(t_UserInterface *ui);

t_UserInterfaceButton   *ft_UserInterfaceCreateButton(float x, float y, float w, float h, Texture2D *tex, Color color);
void                    ft_UserInterfaceSetButtonData(t_UserInterfaceButton *butt, void *data);
void                    ft_UserInterfaceLstPushButton(t_UserInterface *ui, t_UserInterfaceButton *button);
void                    ft_UserInterfaceLstPushButtonBack(t_UserInterface *ui, t_UserInterfaceButton *button);

void                    ft_UserInterfaceLinkButton(t_UserInterfaceButton *button,
                            void (*fptr_action)(t_UserInterfaceButton *self, void *data_vars));

bool                    ft_UserInterfaceClick(void *data_vars, t_UserInterface *ui);

void                    ft_UserInterfaceDraw(t_UserInterface *ui);


//  - - - - VARS DATA               - - - -
typedef struct  s_Vars
{
    t_Grid          *grid;
    t_UserInterface *ui;
}   t_Vars;

//  VarsInit.c
int     ft_VarsInit(t_Vars *vars);

//  VarsUpdate.c
void    ft_VarsUpdate(t_Vars *vars);

//  VarsDraw.c
void    ft_VarsDraw(t_Vars *vars);

//  VarsFree.c
void    ft_VarsFree(t_Vars *vars);

#endif