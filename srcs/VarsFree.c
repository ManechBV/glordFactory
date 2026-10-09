#include "vars.h"

void    ft_VarsFree(t_Vars *vars)
{
    ft_FreeGrid(vars->grid);
}