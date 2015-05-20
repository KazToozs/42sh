/*
** keys_check.c for termcaps in /home/fernan_s/Desktop/termcaps/src
** 
** Made by Quentin Fernandez
** Login   <fernan_s@epitech.net>
** 
** Started on  Sun May 17 03:57:33 2015 Quentin Fernandez
** Last update Tue May 19 09:17:23 2015 Quentin Fernandez
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

int		home_of_str(t_arg *arg)
{
  while (arg->str->prev)
    go_left(arg);
  return (0);
}

int		go_to_end(t_arg *arg)
{
  while (arg->str->next)
    go_right(arg);
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

t_key		func_key[] =
  {
    {BACK_KEYS, del_left},
    {RIGHT_KEYS, go_right},
    {LEFT_KEYS, go_left},
    {DEL_KEYS, del_key_func},
    {CTRL_D, ctrl_d_key},
    {HOME_KEYS, home_of_str},
    {CTRL_A_KEYS, home_of_str},
    {CTRL_E_KEYS, go_to_end},
    {END_KEYS, go_to_end},
    {0, NULL}
  };

int		is_cmd_key(unsigned char *keys)
{
  while (*keys)
    {
      if (!(*keys >= 0x20 && *keys != 0x7F && *keys != 0x9b))
	return (1);
      keys++;
    }
  return (0);
}

int		key_check(t_arg *arg, char *keys)
{
  long		key;
  int		i;
  struct winsize	w;

  key = (*(long *)keys);
  i = 0;
  ioctl(0, TIOCGWINSZ, &w);
  if (is_cmd_key((unsigned char *) keys))
    {
      while (func_key[i].func && func_key[i].key != key)
	i++;
      if (func_key[i].func)
	return (func_key[i].func(arg));
    }
  else
    {
      arg->size++;
      arg->pos++;
      arg->str = add_elem_to_list(arg->str, keys);
      print_list(arg, arg->str);
      if ((arg->pos % w.ws_col) == 0)
	get_down(w.ws_col); 
    }
  return (0);
}
