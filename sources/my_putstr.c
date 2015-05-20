/*
** my_putstr.c for my_putstr in /home/toozs-_c/ProgElem_test/push_swap_tests/lib_maker
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Thu Dec  4 11:12:29 2014 cristopher toozs-hobson
** Last update Wed May 20 12:55:06 2015 cristopher toozs-hobson
*/

#include <unistd.h>
#include "my.h"

void	my_putstr(char *str)
{
  int	i;

  i = 0;
  if (str == NULL)
    return ;
  while (str[i] != '\0')
    {
      my_putchar(str[i]);
      i++;
    }
}

void    my_putstr_err(char *str)
{
  if (str == NULL)
    return ;
  write(2, (unsigned char *)str, my_strlen(str));
}
