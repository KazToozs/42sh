/*
** my_strcat.c for my_strcat in /home/toozs-_c/rendu/Piscine_C_J07
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Wed Oct  8 20:20:31 2014 cristopher toozs-hobson
** Last update Thu May 14 11:21:00 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include "my.h"

char		*new_str(char *first, char *second)
{
  char		*new;
  int		size_one;
  int		size_two;
  int		i;
  int		n;

  size_one = my_strlen(first);
  size_two = my_strlen(second);
  i = 0;
  n = 0;
  if ((new = malloc(sizeof(char) * (size_one + size_two + 1))) == NULL)
    return (NULL);
  while (first[i] != '\0')
    {
      new[i] = first[i];
      i++;
    }
  while (second != NULL && second[n] != '\0')
    {
      new[i] = second[n];
      i++;
      n++;
    }
  new[i] = '\0';
  return (new);
}

char		*my_strcat(char *first, char *second, int option)
{
  char		*new;

  if (first == NULL && second == NULL)
    return (NULL);
  new = new_str(first, second);
  if (option == 1)
    free(first);
  else if (option == 2)
    free(second);
  else if (option == 3)
    {
      free(first);
      free(second);
    }
  return (new);
}
