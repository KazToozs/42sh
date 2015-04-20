/*
** fork_manage.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Mon Feb 16 11:41:25 2015 cristopher toozs-hobson
** Last update Sat Feb 28 22:55:07 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "minishell.h"

int		chain_count(t_env *tab)
{
  int		i;

  i = 0;
  while (tab != NULL)
    {
      tab = tab->next;
      i++;
    }
  return (i);
}

char		**create_env(t_env *env)
{
  int		i;
  char		**tab;

  i = 0;
  tab = malloc(sizeof(char *) * (chain_count(glo.env) + 1));
  if (tab == NULL)
    exit(1);
  while (env != NULL)
    {
      tab[i] = env->var;
      i++;
      env = env->next;
    }
  tab[i] = NULL;
  return (tab);
}

void		execute_fork(char **word_tab, t_env *env)
{
  int		status;
  char		**tab;

  if ((glo.pid = fork()) == - 1)
    manage_error("Fork failed\n");
  else if (glo.pid == 0)
    {
      tab = create_env(env);
      if (execve(word_tab[0], word_tab, tab) == -1)
	exit(1);
    }
  else
    {
      if (waitpid(glo.pid, &status, 0) == -1)
	exit(1);
      glo.pid = 0;
    }
}
