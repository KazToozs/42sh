/*
** auxilary.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Tue Mar  3 11:01:56 2015 cristopher toozs-hobson
** Last update Fri May  1 16:51:25 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include "minishell.h"
#include "my.h"

void		my_show_list(t_env *list)
{
  t_env		*tmp;

  tmp = list;
  while (tmp != NULL)
    {
      if (tmp->var != NULL)
        {
          my_putstr(tmp->var);
          my_putchar('\n');
        }
      tmp = tmp->next;
    }
}

void		free_tab(char **tab)
{
  int		i;

  i = 0;
  if (tab != NULL)
    {
      while (tab[i] != NULL)
        {
          free(tab[i]);
          i++;
        }
      free(tab);
    }
}

int		row_count(char **tab)
{
  int		i;

  i = 0;
  while (tab[i] != NULL)
    i++;
  return (i);
}
