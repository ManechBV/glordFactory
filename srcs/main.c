#include "vars.h"

int main(void)
{
    InitWindow(1280, 720, "Glorb Factory");

    t_Vars  Vars;

    if (ft_VarsInit(&Vars) != 0)
        return (ft_ErrorInt("ft_VarsInit() failed!", 420));

    while (!WindowShouldClose())
    {
        ft_VarsUpdate(&Vars);

        BeginDrawing();
            ClearBackground(BLACK);
            ft_VarsDraw(&Vars);
        EndDrawing();
    }

    ft_VarsFree(&Vars);

    CloseWindow();

    return 0;
}