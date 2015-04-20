/*
** my_strcat.c for my_strcat in /home/toozs-_c/rendu/Piscine_C_J07
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Wed Oct  8 20:20:31 2014 cristopher toozs-hobson
** Last update Wed Mar 25 10:01:50 2015 cristopher toozs-hobson
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
    exit(0);
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

char		*my_strcat(char *first, char *second)
{
  char		*new;

  if (first == NULL && second == NULL)
    return (NULL);
  new = new_str(first, second);
  return (new);
}
