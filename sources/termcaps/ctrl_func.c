/*
** ctrl_func.c for  in /home/fernan_s/rendu/PSU/PSU_2014_42sh/sources/termcaps
** 
** Made by Quentin Fernandez
** Login   <fernan_s@epitech.net>
** 
** Started on  Wed May 20 20:18:36 2015 Quentin Fernandez
** Last update Fri May 22 19:48:37 2015 cristopher toozs-hobson
*/

#include "termcaps.h"

int		clear_l_screen(t_arg *arg)
{
  int		i;
  int		old_pos;

  while (arg->str->prev)
    arg->str = arg->str->prev;
  put_str(tgetstr("cl", NULL));
  display_prompt(1, g_glo.env);
  old_pos = arg->pos;
  arg->pos = strlen(g_glo.prompt);
  i = arg->pos;
  print_list(arg, arg->str);
  while (i++ < old_pos)
    go_right(arg);
  return (0);
}

int		isseparator(char *str)
{
  char		*separator;
  int		i;

  if (!str)
    return (0);
  separator = " -_\t";
  i = 0;
  while (separator[i])
    {
      if (str[0] == separator[i++])
	return (1);
    }
  return (0);
}

int		left_word(t_arg *arg)
{
  while (arg->str->prev && 0 == isseparator(arg->str->val))
    go_left(arg);
  while (arg->str->prev && isseparator(arg->str->val))
    go_left(arg);
  return (0);
}

int		right_word(t_arg *arg)
{
  while (arg->str->next->next && 0 == isseparator(arg->str->next->val))
    go_right(arg);
  while (arg->str->next->next && isseparator(arg->str->next->val))
    go_right(arg);
  return (0);
}
