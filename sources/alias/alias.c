/*
** alias.c for 42sh in /home/pallua_j/tmp/alias/src
** 
** Made by Jules Palluau
** Login   <pallua_j@epitech.net>
** 
** Started on  Tue May  5 10:01:21 2015 Jules Palluau
** Last update Wed May 20 13:26:59 2015 Quentin Fernandez
*/

#include "alias.h"

t_file		*init_alias(t_main *m)
{
  if ((m->file = malloc(sizeof(t_file))) == NULL)
    return (NULL);
  m->file->alias = NULL;
  if ((m->file->fd = open(ALIAS_FILE, O_CREAT | O_RDWR,
		       00644)) == -1)
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

/* int		check_builtal(char *s, t_file *file) */
/* { */
/*   char		**tab; */
  
/*   if ((tab = my_str_tab(s)) == NULL) */
/*     return (-1); */
/*   if (my_strcmp(tab[0], "alias") == 0) */
/*     file->alias = built_alias(file, s); */
/*   else if (my_strcmp(tab[0], "export") == 0) */
/*     built_export(file, s); */
/*   free_tab(tab); */
/*   if (file->statement == 1) */
/*     return (-1); */
/*   return (0); */
/* } */

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
  /* if (check_builtal(s, file) == -1) */
  /*   return (NULL); */
  return (new);
}
