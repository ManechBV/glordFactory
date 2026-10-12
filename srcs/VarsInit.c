#include "vars.h"

static void ft_ButtonSetGridPaintType(t_UserInterfaceButton *self, void *data_vars)
{
    t_Vars          *vars = (t_Vars*) data_vars;
    e_GridTileType  *type = (e_GridTileType*) self->data;

    vars->grid->paint_type = *type;
    printf("Just set paint type to %d\n", *type);
}

int ft_VarsInit(t_Vars *vars)
{
    t_TexArr    *grid_tex_arr;

    //  Load textures
    {
        uint16_t    nb_textures = 4;
        char *paths[] = {
            "res/empty_tile.png",
            "res/belt_tile.png",
            "res/seller_tile.png",
            "res/spawner_tile.png"};
        grid_tex_arr = ft_CreateTextureArray(nb_textures, paths);
    }
    if (grid_tex_arr == NULL)
        return (1);
    //  Finished loading textures

    //  Create empty grid filled with ground tiles
    vars->grid = ft_CreateGrid(20, 20, grid_tex_arr);
    if (vars->grid == NULL)
        return (1);
    ft_GridSetScale(vars->grid, 32.0f);
    ft_GridSetOffset(vars->grid, 0.0f, 0.0f);
    //  Finished Creating grid

    //  Create user interface and add buttons
    vars->ui = ft_CreateUserInterface();

    {
        int             x = 10;
        e_GridTileType  type_tex = GRIDTILE_EMPTY;

        while (type_tex <= GRIDTILE_SPAWNER)
        {
            t_UserInterfaceButton*  butt = ft_UserInterfaceCreateButton(
                x, GetScreenHeight() - 42, 32, 32,
                ft_TexArrGet(grid_tex_arr, type_tex), WHITE);
            
            butt->data = malloc(sizeof(e_GridTileType));
            if (!(butt->data))
                return (1);
            *((e_GridTileType*)(butt->data)) = type_tex;
            ft_UserInterfaceLinkButton(butt, ft_ButtonSetGridPaintType);

            ft_UserInterfaceLstPushButton(vars->ui, butt);

            x += 42;
            type_tex++;
        }

        //  Little background for da buttons
        ft_UserInterfaceLstPushButtonBack(vars->ui,
            ft_UserInterfaceCreateButton(
                0, GetScreenHeight() - 52,
                x + 10, 52,
                NULL,
                GRAY));
    }
    //  Finished Creating user interface

    return (0);
}
