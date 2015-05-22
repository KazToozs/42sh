/*
** keys_check.c for termcaps in /home/fernan_s/Desktop/termcaps/src
** 
** Made by Quentin Fernandez
** Login   <fernan_s@epitech.net>
** 
** Started on  Sun May 17 03:57:33 2015 Quentin Fernandez
** Last update Fri May 22 18:56:46 2015 cristopher toozs-hobson
*/

#include "termcaps.h"

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
    {CTRL_LEFT_KEYS, left_word},
    {CTRL_RIGHT_KEYS, right_word},
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

int			key_check(t_arg *arg, char *keys)
{
  long			key;
  int			i;
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
