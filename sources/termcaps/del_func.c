/*
** del_func.c for  in /home/fernan_s/rendu/PSU/PSU_2014_42sh/sources/termcaps
** 
** Made by Quentin Fernandez
** Login   <fernan_s@epitech.net>
** 
** Started on  Wed May 20 20:16:19 2015 Quentin Fernandez
** Last update Wed May 20 20:17:24 2015 Quentin Fernandez
*/

#include "termcaps.h"

int		ctrl_d_key(t_arg *arg)
{
  if (arg->str->val == NULL && arg->str->next == NULL)
    return (1);
  if (arg->str->next)
    {
      arg->size--;
      arg->str->next = rm_to_next_elem(arg->str->next);
      save_pos();
      if (arg->str->next)
	print_list_del(arg, arg->str->next);
      put_c(' ');
      load_pos();
    }
  return (0);
}

int		del_key_func(t_arg *arg)
{
  if (arg->str->next)
    {
      arg->size--;
      arg->str->next = rm_to_next_elem(arg->str->next);
      save_pos();
      if (arg->str->next)
	print_list_del(arg, arg->str->next);
      put_c(' ');
      load_pos();
    }
  return (0);
}
