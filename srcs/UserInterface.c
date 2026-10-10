#include "vars.h"

t_UserInterface *ft_CreateUserInterface(void)
{
    t_UserInterface *ui;

    ui = malloc(sizeof(t_UserInterface));
    if (!ui)
        return (ft_Error("Failed to malloc t_UserInterface in ft_CreateUserInterface."));
        
    ui->buttons_lst = NULL;
    ui->hidden = false;
    ui->len = 0;
    return (ui);
}

void    ft_FreeUserInterface(t_UserInterface *ui)
{
    t_UserInterfaceButton   *curr;

    curr = ui->buttons_lst;
    if (curr)
    {
        while (curr)
        {
            t_UserInterfaceButton   *tmp;
            tmp = curr->next;
            if (curr->data != NULL)
                free(curr->data);
            free(curr);
            curr = tmp;
        }
    }
    free(ui);
}

static void ft_ButtonDoNothing(t_UserInterfaceButton *self, void *data_vars)
{
    //printf("Button succesfully did nothing! fucking amazing\n");
}

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
    button->data = NULL;
    button->fptr_pressed = ft_ButtonDoNothing;
    button->tex_ptr = tex;
    button->color = color;
    return (button);
}

void    ft_UserInterfaceSetButtonData(t_UserInterfaceButton *butt, void *data)
{
    butt->data = data;
}

void    ft_UserInterfaceLinkButton(t_UserInterfaceButton *button,
    void (*fptr_action)(t_UserInterfaceButton *self, void *data_vars))
{
    button->fptr_pressed = fptr_action;
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

void    ft_UserInterfaceLstPushButtonBack(t_UserInterface *ui, t_UserInterfaceButton *button)
{
    if (ui->buttons_lst == NULL)
    {
        ui->buttons_lst = button;
        return ;
    }

    t_UserInterfaceButton   *curr = ui->buttons_lst;

    button->next = curr;
    ui->buttons_lst = button;
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

static bool    ft_IsMouseOnButton(t_UserInterfaceButton *butt)
{
    Vector2 mous = GetMousePosition();

    if (mous.x < butt->x)
        return (false);
    if (mous.x > (butt->x + butt->w))
        return (false);
    if (mous.y < butt->y)
        return (false);
    if (mous.y > (butt->y + butt->h))
        return (false);
    return (true);
}

bool    ft_UserInterfaceClick(void *data_vars, t_UserInterface *ui)
{
    t_UserInterfaceButton   *curr;
    bool                    button_clicked = false;

    curr = ui->buttons_lst;
    while (curr)
    {
        if (ft_IsMouseOnButton(curr))
        {
            curr->fptr_pressed(curr, data_vars);
            button_clicked = true;
        }
        curr = curr->next;
    }
    return (button_clicked);
}