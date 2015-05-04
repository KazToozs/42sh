/*
** env.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Mon Feb 16 11:32:54 2015 cristopher toozs-hobson
** Last update Fri May  1 15:41:52 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include "minishell.h"
#include "my.h"

int		my_put_in_list_end(t_env **list, char *data, t_env **mark)
{
  t_env		*block;
  t_env		*tmp;

  if ((block = malloc(sizeof(*block))) == NULL)
    return (1);
  block->var = data;
  block->next = NULL;
  if ((*list) == NULL)
    {
      block->prev = NULL;
      (*mark) = block;
    }
  else
    {
      tmp = (*list);
      while ((*list)->next != NULL)
        (*list) = (*list)->next;
      (*list)->next = block;
      (*list)->next->prev = (*list);
      (*list) = tmp;
    }
  return (0);
}

void		remove_node(t_env **node, t_env **mark)
{
  t_env		*tmp;

  tmp = (*node);
  if ((*node)->prev != NULL)
    (*node)->prev->next = (*node)->next;
  if ((*node)->next != NULL)
    (*node)->next->prev = (*node)->prev;
  if ((*node)->prev == NULL)
    (*mark) = (*mark)->next;
  free(tmp);
}

char		*find_var(t_env *env, char *var)
{
  char		**tab;

  while (env != NULL)
    {
      tab = my_str_tab(env->var);
      if (my_strcmp(var, tab[0]) == 0)
        {
          free_tab(tab);
          return (env->var);
        }
      free_tab(tab);
      env = env->next;
    }
  return (NULL);
}

int		make_env(char **env, t_main *m)
{
  int		i;

  i = 0;
  m->env = NULL;
  while (env[i] != NULL)
    {
      if (my_put_in_list_end(&m->env, env[i], &m->env) == 1)
	return (1);
      i++;
    }
  return (0);
}
