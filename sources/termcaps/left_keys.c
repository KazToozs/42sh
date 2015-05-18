/*
** left_keys.c for  in /home/fernan_s/Desktop/termcaps/src
** 
** Made by Quentin Fernandez
** Login   <fernan_s@epitech.net>
** 
** Started on  Sun May 17 04:44:03 2015 Quentin Fernandez
** Last update Mon May 18 14:15:35 2015 cristopher toozs-hobson
*/

#include "termcaps.h"

int             del_left(t_arg *arg)
{
  if (arg->str->prev)
    {
      arg->str = rm_prev_elem(arg->str);
      arg->pos--;
      arg->size--;
      get_back(arg);
      save_pos();
      if (arg->str->next)
	print_list_del(arg, arg->str->next);
      put_c(' ');
      load_pos();
    }
  return (0);
}

int             go_left(t_arg *arg)
{
  if (arg->str && arg->str->prev)
    {
      arg->str = arg->str->prev;
      arg->pos--;
      get_back(arg);
    }
  return (0);
}

void                    get_back(t_arg *arg)
{
  struct winsize        w;

  ioctl(0, TIOCGWINSZ, &w);
  if (((arg->pos + 1) % w.ws_col) == 0)
    get_up(w.ws_col);
  else
    tputs(tgetstr("le", NULL), 0, put_c);
}

void                    get_up(int l)
{
  tputs(tgetstr("up", NULL), 1, put_c);
  while (l--)
    tputs(tgetstr("nd", NULL), 1, put_c);
}

