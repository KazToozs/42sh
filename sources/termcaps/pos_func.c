/*
** pos_func.c for  in /home/fernan_s/Desktop/termcaps/src
** 
** Made by Quentin Fernandez
** Login   <fernan_s@epitech.net>
** 
** Started on  Sun May 17 04:42:54 2015 Quentin Fernandez
** Last update Wed May 20 20:15:22 2015 Quentin Fernandez
*/

#include "termcaps.h"

void	save_pos()
{
  tputs(tgetstr("sc", NULL), 1, put_c);
}

void	load_pos()
{
  tputs(tgetstr("rc", NULL), 1, put_c);
}

int	home_of_str(t_arg *arg)
{
  while (arg->str->prev)
    go_left(arg);
  return (0);
}

int	go_to_end(t_arg *arg)
{
  while (arg->str->next)
    go_right(arg);
  return (0);
}
