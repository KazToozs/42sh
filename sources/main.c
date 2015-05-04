/*
** main.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Wed Feb  4 15:15:44 2015 cristopher toozs-hobson
** Last update Fri May  1 16:35:02 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include "my.h"
#include "minishell.h"

g_glo		glo;
extern char	**environ;

int		start_up(t_main *m)
{
  my_putstr("$>");
  glo.x = 1;
  glo.pid = -2;
  m->ret = 0;
  if (make_env(environ, m) == 1)
    return (1);
  if (manage_signal() == 1)
    return (1);
  return (0);
}

void		free_env(t_env *env)
{
  t_env		*tmp;

  tmp = env;
  while (env != NULL)
    {
      env = env->next;
      free(tmp);
      tmp = env;
    }
}

int		main()
{
  char		*ret;
  int		check;
  t_main	m;

  if (start_up(&m) == 1)
    return (1);
  while ((ret = get_next_line(0)) != NULL)
    {
      if ((check = my_shell(ret, &m)) != -3)
	{
	  free(ret);
	  free_env(m.env);
	  return (check);
	}
      my_putstr("$>");
      free(ret);
    }
  return (0);
}
