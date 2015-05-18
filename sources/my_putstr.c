/*
** my_putstr.c for my_putstr in /home/toozs-_c/ProgElem_test/push_swap_tests/lib_maker
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Thu Dec  4 11:12:29 2014 cristopher toozs-hobson
** Last update Mon May 18 14:37:35 2015 cristopher toozs-hobson
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
