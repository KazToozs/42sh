/*
** my_realloc.c for allum1 in /home/toozs-_c/Prog_tests/allum1
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Wed Feb 11 17:26:37 2015 cristopher toozs-hobson
** Last update Sat Feb 28 23:01:24 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include "minishell.h"
#include "my.h"

char		*my_realloc(char *buffer, int size)
{
  int		i;
  char		*tmp;

  if ((tmp = malloc(size)) == NULL)
    exit(0);
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
    exit(0);
  i = 0;
  while (i < (size - 1))
    {
      tmp[i] = my_strdup(buffer[i]);
      tmp[i] = my_strcpy(tmp[i], buffer[i]);
      i++;
    }
  tmp[i] = NULL;
  free_tab(buffer);
  return (tmp);
}
