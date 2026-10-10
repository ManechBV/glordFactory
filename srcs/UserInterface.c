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