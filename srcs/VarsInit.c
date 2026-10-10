#include "vars.h"

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

    vars->grid = ft_CreateGrid(20, 20, grid_tex_arr);
    if (vars->grid == NULL)
        return (1);

    ft_GridSetScale(vars->grid, 32.0f);
    ft_GridSetOffset(vars->grid, 0.0f, 0.0f);

    vars->ui = ft_CreateUserInterface();
    ft_UserInterfaceLstPushButton(vars->ui,
        ft_UserInterfaceCreateButton(0, 0, 50, 60, NULL, RED));
    ft_UserInterfaceLstPushButton(vars->ui,
        ft_UserInterfaceCreateButton(100, 0, 50, 200, ft_TexArrGet(grid_tex_arr, GRIDTILE_SPAWNER), WHITE));

    return (0);
}
