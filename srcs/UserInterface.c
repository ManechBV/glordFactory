#include "vars.h"

t_UserInterface *ft_CreateUserInterface(void)
{
    t_UserInterface *ui;

    ui = malloc(sizeof(t_UserInterface));
    if (!ui)
        return (ft_Error("Failed to malloc t_UserInterface in ft_CreateUserInterface."));
    
    ui->hidden = false;
    ui->len = 0;
    ui->tex_arr = NULL;
    return (ui);
}

static void ft_ButtonDoNothing(void *data)
{}

static t_UserInterfaceButton    *ft_CreateButton(float x, float y, float w, float h, Texture2D *tex)
{
    t_UserInterfaceButton   *button;

    button = malloc(sizeof(t_UserInterfaceButton));
    if (!button)
        return (ft_Error("Failed to malloc t_UserInterfaceButton in ft_CreateButton."));
    
    button->x = x;
    button->y = y;
    button->w = w;
    button->h = h;
    button->next = NULL;
    button->fptr_pressed = ft_ButtonDoNothing;
    return (button);
}