/*
** my_strdup.c for my_strdup in /home/pallua_j/rendu/Piscine_C_J08/ex_01
** 
** Made by jules palluau
** Login   <pallua_j@epitech.net>
** 
** Started on  Wed Oct  8 11:29:19 2014 jules palluau
** Last update Tue May 19 12:49:03 2015 msa_m
*/

#include "test.h"

char	*my_strdup(char *src)
{
  int	l;
  int	x;
  char	*str;

  x = 0;
  l = my_strlen(src) + 1;
  if ((str = malloc(l)) == NULL)
    return (NULL);
  while (src[x] != '\0')
    {
      str[x] = src[x];
      x++;
    }
  return (str);
}
