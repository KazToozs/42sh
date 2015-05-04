/*
** my_getnbr.c for my_getnbr in /home/pallua_j/rendu/Piscine_C_J07/lib/my
** 
** Made by jules palluau
** Login   <pallua_j@epitech.net>
** 
** Started on  Wed Oct  8 10:23:41 2014 jules palluau
** Last update Tue Apr 21 14:05:25 2015 cristopher toozs-hobson
*/

#include "my.h"

int	my_error(int x, char *str)
{
  int	nb;

  nb = x;
  while (str[nb] >= '0' && str[nb] <= '9')
    nb++;
  if (nb > 10)
    return (0);
  else if (nb == 10)
    {
      if (my_strncmp(&str[x], "2147483647", nb) > 0)
        return (0);
    }
  return (1);
}

int	my_str_isnum(char *str)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  if (str == 0)
    return (1);
  if (str[i] == '-')
    i++;
  while (str[i] != '\0')
    {
      if (j > 1)
        return (0);
      if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.')
        {
          if (str[i] == '.')
            j++;
          i++;
        }
      else
        return (0);
    }
  return (1);
}

int	my_getnbr(char *str)
{
  int	result;
  int	x;

  if (my_str_isnum(str) == 0)
    {
      my_putstr_err("Argument is not a good number\n");
      return (0);
    }
  result = 0;
  x = 0;
  while (str[x] != '\0' && (str[x] == '+' || str[x] == '-'))
    x++;
  if (*str == '+')
    return (my_getnbr(str = str + 1));
  if (*str == '-')
    return (-my_getnbr(str = str + 1));
  if (my_error(x, str) != 1)
    return (0);
  while (str[x] && str[x] >= '0' && str[x] <= '9')
    {
      result *= 10;
      result = result + str[x] - 48;
      x = x + 1;
    }
  return (result);
}
