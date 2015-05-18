/*
** pos_func.c for  in /home/fernan_s/Desktop/termcaps/src
** 
** Made by Quentin Fernandez
** Login   <fernan_s@epitech.net>
** 
** Started on  Sun May 17 04:42:54 2015 Quentin Fernandez
** Last update Sun May 17 04:43:16 2015 Quentin Fernandez
*/

#include "termcaps.h"

void            save_pos()
{
  tputs(tgetstr("sc", NULL), 1, put_c);
}

void            load_pos()
{
  tputs(tgetstr("rc", NULL), 1, put_c);
}
