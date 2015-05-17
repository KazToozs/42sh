/*
** my_realloc.c for allum1 in /home/toozs-_c/Prog_tests/allum1
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Wed Feb 11 17:26:37 2015 cristopher toozs-hobson
** Last update Sun May 17 10:26:57 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include "minishell.h"
#include "my.h"

char		*my_realloc(char *buffer, int size)
{
  int		i;
  char		*tmp;

  if ((tmp = malloc(size)) == NULL)
    return (NULL);
  i = 0;
  while (buffer[i] != '\0')
    {
      tmp[i] = buffer[i];
      i++;
    }
  while (i < size)
    tmp[i++] = '\0';
  free(buffer);
  return (tmp);
}

char		**my_realloc_tab(char **buffer, int size)
{
  int		i;
  char		**tmp;

  if ((tmp = malloc(sizeof(char *) * (size + 1))) == NULL)
    return (NULL);
  i = 0;
  while (i < (size - 1))
    {
      if ((tmp[i] = my_strdup(buffer[i])) == NULL)
	return (NULL);
      tmp[i] = my_strcpy(tmp[i], buffer[i]);
      i++;
    }
  tmp[i] = NULL;
  free_tab(buffer);
  return (tmp);
}
