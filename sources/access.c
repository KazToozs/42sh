/*
** access.c for 42sh in /home/toozs-_c/Prog_tests/fourty_two_tests/sources
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Mon Apr 27 16:33:28 2015 cristopher toozs-hobson
** Last update Sun May 17 12:06:00 2015 cristopher toozs-hobson
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"

char		*path_access(char **tab, char *function, int i)
{
  char		*tmp;
  char		*ret;

  tmp = tab[i];
  if (access((ret = my_strcat(tab[i], function, 0)), F_OK) == 0)
    {
      free(tmp);
      while (tab[++i] != NULL)
        free(tab[i]);
      free(tab);
      return (ret);
    }
  free(ret);
  free(tab[i]);
  return (NULL);
}

int		check_slash(char *function)
{
  int		i;

  i = my_strlen(function) - 1;
  while (i >= 0)
    {
      if (function[i] == '/')
        return (1);
      i--;
    }
  return (0);
}

char		*check_access(char **tab, char *function)
{
  char		*ret;
  int		i;

  i = 1;
  if (check_slash(function) == 1)
    {
      if (access(function, F_OK) == 0)
        {
          while (tab && tab[++i] != NULL)
            free(tab[i]);
          free(tab);
          return (function);
        }
    }
  else while (tab && tab[i] != NULL)
	 {
	   if ((ret = path_access(tab, function, i)) != NULL)
	     return (ret);
	   i++;
	 }
  if (tab)
    free(tab);
  return (NULL);
}
