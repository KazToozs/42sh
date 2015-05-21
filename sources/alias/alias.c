/*
** alias.c for 42sh in /home/pallua_j/tmp/alias/src
** 
** Made by Jules Palluau
** Login   <pallua_j@epitech.net>
** 
** Started on  Tue May  5 10:01:21 2015 Jules Palluau
** Last update Thu May 21 13:55:17 2015 cristopher toozs-hobson
*/

#include "alias.h"

t_file		*init_alias(t_main *m)
{
  if ((m->file = malloc(sizeof(t_file))) == NULL)
    return (NULL);
  m->file->alias = NULL;
  if ((m->file->fd = open(ALIAS_FILE, O_CREAT | O_RDWR, 00644)) == -1)
    return (NULL);
  m->file->statement = 0;
  m->file->alias = source(m);
  if (m->file->statement != 0)
    return (NULL);
  return (m->file);
}

char		*create_alias(char *s, t_alias *alias)
{
  char		**tab;
  char		*new;
  int		x;
  t_alias	*tmp;

  if ((tab = my_alias_tab(s)) == NULL)
    return (NULL);
  x = -1;
  while (tab[++x] != NULL)
    {
      tmp = alias;
      while (tmp != NULL)
	{
	  if (my_strcmp(tmp->src, tab[x]) == 0)
	    {
	      free(tab[x]);
	      tab[x] = my_strdup(tmp->new);
	    }
	  tmp = tmp->next;
	}
    }
  if ((new = new_line(tab, 0)) == NULL)
    return (NULL);
  free_tab(tab);
  return (new);
}

char		*alias(char *s, t_file *file)
{
  char		*new;
  int		x;
  char		**tab;

  x = 0;
  if ((new = create_alias(s, file->alias)) == NULL)
    return (NULL);
  if ((tab = my_alias_tab(new)) == NULL)
    return (NULL);
  free(new);
  while (tab[x] != NULL)
    {
      if ((tab[x] = create_alias(tab[x], file->alias)) == NULL)
	return (NULL);
      x++;
    }
  if ((new = new_line(tab, 0)) == NULL)
    return (NULL);
  free_tab(tab);
  return (new);
}
