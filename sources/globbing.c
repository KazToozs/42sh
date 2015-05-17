/*
** globbing.c for 42sh in /home/toozs-_c/Prog_tests/fourty_two_tests/sources
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sun May 17 00:20:17 2015 cristopher toozs-hobson
** Last update Sun May 17 10:57:10 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include <glob.h>
#include "my.h"

char		**set_new(char **old, char **glob_tab, int size, int *i)
{
  char		**new;
  int		first;
  int		middle;
  int		end;

  first = -1;
  middle = -1;
  if ((new = malloc(sizeof(char *) * (size + 1))) == NULL)
    return (NULL);
  while (++first < *i)
    if ((new[first] = my_strdup(old[first])) == NULL)
      return (NULL);
  while (glob_tab[++middle] != NULL)
    if ((new[first++] = my_strdup(glob_tab[middle])) == NULL)
      return (NULL);
  end = *i + 1;
  while (old[end] != NULL)
    if ((new[first++] = my_strdup(old[end++])) == NULL)
      return (NULL);
  new[first] = NULL;
  *i += middle - 1;
  return (new);
}

char		**my_glob_tab(char **old, char **glob_tab, int *i)
{
  char		**new;
  int		old_size;
  int		glob_size;
  int		size;

  old_size = -1;
  glob_size = -1;
  while (old[++old_size] != NULL);
  while (glob_tab[++glob_size] != NULL);
  size = old_size + glob_size;
  new = set_new(old, glob_tab, size, i);
  return (new);
}

char		**globbing(char **exp)
{
  glob_t	lob;
  int		i;

  i = 0;
  while (exp != NULL && exp[i] != NULL)
    {
      if (glob(exp[i], 0, NULL, &lob) == 0)
      	{
      	  if ((exp = my_glob_tab(exp, lob.gl_pathv, &i)) == NULL)
	    return (NULL);
      	}
      globfree(&lob);
      i++;
    }
  return (exp);
}
