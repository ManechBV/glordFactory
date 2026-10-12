#include "vars.h"

static void ft_VarsHandleMouseInput(t_Vars *vars)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        //  Handle user interface buttons input:
        //  if no ui element has been clicked do shit
        //  to prevent the user from clicking shit on the map while
        //  trying to click shit on the ui ta capte
        if (ft_UserInterfaceClick(vars, vars->ui) == false)
        {
            ft_GridPaintTileAtMouse(vars->grid);
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        ft_GridTileRightClick(vars->grid);
    }

    //  Move grid by holding down middle mouse button
    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
    {
        Vector2 mouse_delta = GetMouseDelta();

        ft_GridIncreaseOffset(vars->grid, mouse_delta.x, mouse_delta.y);
    }
}

static void ft_VarsHandleInput(t_Vars *vars)
{
    ft_VarsHandleMouseInput(vars);
}

void    ft_VarsUpdate(t_Vars *vars)
{
    ft_VarsHandleInput(vars);
}