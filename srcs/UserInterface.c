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

t_UserInterfaceButton    *ft_UserInterfaceCreateButton(float x, float y, float w, float h, Texture2D *tex, Color color)
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
    button->tex_ptr = tex;
    button->color = color;
    return (button);
}

void    ft_UserInterfaceLstPushButton(t_UserInterface *ui, t_UserInterfaceButton *button)
{
    if (ui->buttons_lst == NULL)
    {
        ui->buttons_lst = button;
        return ;
    }

    t_UserInterfaceButton   *curr = ui->buttons_lst;
    while (curr->next != NULL)
        curr = curr->next;
    curr->next = button;
}

static void    ft_UserInterfaceDrawButton(t_UserInterfaceButton *button)
{
    if (button->tex_ptr == NULL)
    {
        DrawRectangle(button->x, button->y, button->w, button->h, button->color);
        return ;
    }
    DrawTexturePro(*(button->tex_ptr),
        (Rectangle){0, 0, button->tex_ptr->width, button->tex_ptr->height},
        (Rectangle){button->x, button->y, button->w, button->h},
        (Vector2){0}, 0.0f, button->color);
}

void        ft_UserInterfaceDraw(t_UserInterface *ui)
{
    if (ui->buttons_lst == NULL)
        return ;
    
        t_UserInterfaceButton   *curr;

        curr = ui->buttons_lst;
        while (curr)
        {
            ft_UserInterfaceDrawButton(curr);
            curr = curr->next;
        }
}