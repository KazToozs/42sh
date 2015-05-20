/*
** keys_check.c for termcaps in /home/fernan_s/Desktop/termcaps/src
** 
** Made by Quentin Fernandez
** Login   <fernan_s@epitech.net>
** 
** Started on  Sun May 17 03:57:33 2015 Quentin Fernandez
** Last update Wed May 20 17:10:48 2015 cristopher toozs-hobson
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

int		clear_l_screen(t_arg *arg)
{
  int		i;
  int		old_pos;

  while (arg->str->prev)
    arg->str = arg->str->prev;
  put_str(tgetstr("cl", NULL));
  display_prompt(1, glo.env);
  old_pos = arg->pos;
  arg->pos = strlen(glo.prompt);
  i = arg->pos;
  print_list(arg, arg->str);
  while (i++ < old_pos)
    go_right(arg);
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
    {CTRL_L_KEYS, clear_l_screen},
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

void			check_term()
{
  static int		col = 0;
  struct winsize	w;

  ioctl(0, TIOCGWINSZ, &w);
  if (col == 0)
    col = w.ws_col;
  if (col != w.ws_col)
    {
      clear_l_screen(&glo.arg);
      col = w.ws_col;
    }
}

int		key_check(t_arg *arg, char *keys)
{
  long		key;
  int		i;
  struct winsize	w;

  key = (*(long *)keys);
  i = 0;
  check_term();
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
