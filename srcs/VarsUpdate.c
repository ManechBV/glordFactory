#include "vars.h"

static void ft_VarsHandleMouseInput(t_Vars *vars)
{
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