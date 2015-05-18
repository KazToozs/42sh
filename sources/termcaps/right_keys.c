/*
** right_keys.c for termcaps in /home/fernan_s/Desktop/termcaps/src
** 
** Made by Quentin Fernandez
** Login   <fernan_s@epitech.net>
** 
** Started on  Sun May 17 04:45:36 2015 Quentin Fernandez
** Last update Sun May 17 04:45:55 2015 Quentin Fernandez
*/

#include "termcaps.h"

void                    get_down(int l)
{
  tputs(tgetstr("do", NULL), 1, put_c);
  while (l--)
    tputs(tgetstr("le", NULL), 1, put_c);
}

int                     go_right(t_arg *arg)
{
  struct winsize        w;

  if (arg->str && arg->str->next)
    {
      arg->str = arg->str->next;
      arg->pos++;
      ioctl(0, TIOCGWINSZ, &w);
      if (((arg->pos) % w.ws_col) == 0)
	get_down(w.ws_col);
      else
	tputs(tgetstr("nd", NULL), 1, put_c);
    }
  return (0);
}
