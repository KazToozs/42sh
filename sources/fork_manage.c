/*
** fork_manage.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Mon Feb 16 11:41:25 2015 cristopher toozs-hobson
** Last update Fri May  1 16:17:26 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "minishell.h"
#include "my.h"

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

char		**create_env(t_env *env, t_main *m)
{
  int		i;
  char		**tab;

  i = 0;
  tab = malloc(sizeof(char *) * (chain_count(m->env) + 1));
  if (tab == NULL)
    return (NULL);
  while (env != NULL)
    {
      tab[i] = env->var;
      i++;
      env = env->next;
    }
  tab[i] = NULL;
  return (tab);
}

int		fork_child(char **word_tab, t_env *env, t_main *m)
{
  char		**tab;

  if ((tab = create_env(env, m)) == NULL)
    return (1);
  if (execve(word_tab[0], word_tab, tab) == -1)
    {
      my_putstr_err("Unknown command\n");
      return (1);
    }
  return (1);
}

int		execute_fork(char **word_tab, t_env *env, t_main *m)
{
  int		status;
  pid_t		pid;
  int		ret;

  if ((pid = fork()) == - 1)
    {
      my_putstr_err("Fork failed\n");
      return (1);
    }
  else if (pid == 0)
    {
      glo.pid = 0;
      fork_child(word_tab, env, m);
      return (1);
    }
  else
    {
      if (waitpid(pid, &status, 0) == -1)
	return (1);
      pid = 0;
      if ((ret = status_check(status, m)) != -2)
	return (ret);
    }
  return (1);
}
