/*
** main.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Wed Feb  4 15:15:44 2015 cristopher toozs-hobson
** Last update Wed Mar 25 19:20:30 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include "my.h"
#include "minishell.h"

g_glo		glo;
extern char	**environ;

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
  if (ret[0] == '>' || ret[0] == '<' || ret[0] == '|' || ret[0] == ';')
    return (1);
  else
    return (0);
}

int		main()
{
  char		*ret;

  my_putstr("$>");
  glo.x = 1;
  make_env(environ);
  manage_signal();
  while ((ret = get_next_line(0)) != NULL)
    {
      if (check_quotes(ret) == 0 && check_first(ret) == 0)
	{
	  glo.tree = NULL;
	  make_tree(&glo.tree, ret);
	  launch_tree(glo.tree);
	  free_tree(glo.tree);
	}
      else
	my_putstr_err("Invalid syntax\n");
      my_putstr("$>");
      free(ret);
    }
  return (0);
}
