/*
** my_strncpy.c for my_strncpy in /home/toozs-_c/rendu/Piscine_C_J06/ex_02
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Mon Oct  6 14:37:44 2014 cristopher toozs-hobson
** Last update Wed Mar 25 14:16:19 2015 cristopher toozs-hobson
*/

#include "my.h"

char	*my_strncpy(char *dest, char *src, int n)
{
  int	i;

  i = 0;
  while (i < n && src[i] != '\0')
    {
      dest[i] = src[i];
      i++;
    }
  return (dest);
}
