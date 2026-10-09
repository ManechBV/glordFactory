#ifndef VARS_H
# define VARS_H

# include "raylib.h"
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>

//  ft_Error.c
void    *ft_Error(char *msg);


typedef struct  s_TexArr
{
    uint16_t    len;
    Texture2D   *tex;
}   t_TexArr;

//  TextureArray.c
t_TexArr    *ft_CreateTextureArray(uint16_t ac, char **av);
Texture2D   *ft_TexArrGet(t_TexArr *tex_arr, uint16_t id);


typedef struct  s_Vars
{
    t_TexArr    *tex_arr;
}   t_Vars;

#endif