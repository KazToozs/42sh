/*
** aff_alias.c for 42 in /home/pallua_j/rendu/unix/PSU_2014_42sh/sources/alias
** 
** Made by jules palluau
** Login   <pallua_j@epitech.net>
** 
** Started on  Thu May 21 16:20:04 2015 jules palluau
** Last update Thu May 21 16:32:04 2015 jules palluau
*/

#include "alias.h"

int		alias_err(t_alias *alias, char **tab)
{
  if (tab[1] == NULL)
    {
      aff_alias(alias);
      return (1);
    }
  else if (tablen(tab) < 3)
    {
      fprintf(stderr, "Alias error!\n");
      return (1);
    }
  return (0);
}

int		aff_alias(t_alias *alias)
{
  t_alias	*tmp;

  tmp = alias;
  while (tmp != NULL)
    {
      printf("%s\t%s\n", tmp->src, tmp->new);
      tmp = tmp->next;
    }
  return (0);
}
