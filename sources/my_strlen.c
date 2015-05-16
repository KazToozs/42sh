/*
** my_strlen.c for my_strlen in /home/toozs-_c/rendu/Piscine_C_J04
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Tue Oct  7 11:38:57 2014 cristopher toozs-hobson
** Last update Sat May 16 16:20:51 2015 cristopher toozs-hobson
*/

#include <stdlib.h>

int	my_strlen(char *str)
{
  int	n;

  if (str == NULL)
    return (0);
  n = 0;
  while (str[n] != '\0')
    n++;
  return (n);
}
