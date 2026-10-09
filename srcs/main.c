#include "vars.h"

int main(void)
{
    InitWindow(1280, 720, "Glorb Factory");

    t_Vars  Vars;

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}