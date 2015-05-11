/*
** shell.c for 42sh in /home/toozs-_c/Prog_tests/fourty_two_tests/sources
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Fri May  1 11:50:46 2015 cristopher toozs-hobson
** Last update Wed May  6 17:02:43 2015 cristopher toozs-hobson
*/

#include "minishell.h"
#include "my.h"

int		check_quotes(char *str)
{
  int		i;
  int		odd;

  i = 0;
  odd = 0;
  while (str[i] != '\0')
    {
      if (str[i] == '"' && odd == 0)
        odd = 1;
      else if (str[i] == '"' && odd == 1)
        odd = 0;
      i++;
    }
  return (odd);
}

int		check_first(char *ret)
{
  if (ret[0] == '|' || ret[0] == ';'
      || ret[0] == '&')
    return (1);
  else
    return (0);
}

int		interpret_command(char *ret, t_main *m)
{
  int		check;

  m->tree = NULL;
  if (ret[0] != '\0')
    {
      if (make_tree(&m->tree, ret) == 1)
	return (1);
      show_tree(m->tree, 0);
      check = launch_tree(m->tree, m);
      if (glo.pid != 0)
	glo.pid = -1;
      free_tree(m->tree);
      return (check);
    }
  return (0);
}

int		my_shell(char *ret, t_main *m)
{
  int		check;

  if (check_quotes(ret) == 0 && check_first(ret) == 0)
    {
      glo.pid = -1;
      check = interpret_command(ret, m);
      if (glo.pid == 0)
        {
          return (check);
        }
      if (glo.pid == -1 && check == -3)
        return (m->ret);
      m->ret = check;
      glo.pid = -2;
    }
  else
    {
      my_putstr_err("Invalid syntax\n");
      m->ret = 1;
      return (-3);
    }
  return (-3);
}
