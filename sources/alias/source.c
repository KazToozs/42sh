/*
** source.c for 42sh in /home/pallua_j/tmp/alias/src
** 
** Made by jules palluau
** Login   <pallua_j@epitech.net>
** 
** Started on  Sun May 10 20:03:02 2015 jules palluau
** Last update Mon May 18 17:36:22 2015 jules palluau
*/

#include "alias.h"

int		built_alias(t_main *m)
{
  char		*ne;
  char		**tab;

  if ((tab = my_str_to_wordtab(m->file->exp)) == NULL)
    {
      m->file->statement = 1;
      return (1);
    }
  if (tablen(tab) < 3)
    {
      printf("Alias error\n");
      return (1);
    }
  if ((ne = new_line(tab, 2)) == NULL)
    {
      m->file->statement = 1;
      return (1);
    }
  if ((m->file->alias = my_put_alias_list(m->file->alias, tab[1], ne)) == NULL)
    {
      m->file->statement = 1;
      return (1);
    }
  free(ne);
  return (0);
}

int	built_export(t_main *m)
{
  char	*new;
  char	**tab;

  if ((tab = my_str_to_wordtab(m->file->exp)) == NULL)
    {
      m->file->statement = 1;
      return (1);
    }
  if (tablen(tab) < 3)
    {
      printf("Alias error\n");
      return (1);
    }
  if ((new = new_line(tab, 2)) == NULL)
    {
      m->file->statement = 1;
      return (1);
    }
  add_env(tab[1], new);
  free(new);
  return (0);
}

t_alias		*source(t_main *m)
{
  char		*s;
  char		**tab;

  while ((s = get_next_line(m->file->fd)) != NULL)
    {
      if (s[0] != '\0')
	{
	  if ((tab = my_str_to_wordtab(s)) == NULL)
	    {
	      m->file->statement = 1;
	      return (NULL);
	    }
	  if (my_strcmp(tab[0], "alias") == 0)
	    {
	      m->file->exp = s;
	      built_alias(m);
	    }
	  else if (my_strcmp(tab[0], "export") == 0)
	    {
	      m->file->exp = s;
	      built_export(m);
	    }
	  free(s);
	  free_tab(tab);
	  if (m->file->statement == 1)
	    return (NULL);
	}
    }
  return (m->file->alias);
}

int		built_source(t_main *m)
{
  if (m->word_tab[1] == NULL)
    my_putstr_err("String unvailable!\n");
  else if ((m->file->fd = open(m->word_tab[1], O_RDONLY)) == -1)
    my_putstr_err("Can't find config file!\n");
  m->file->alias = source(m);
  if (m->file->statement != 0)
    return (1);
  return (0);
}
