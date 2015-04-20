/*
** my_putstr.c for my_putstr in /home/toozs-_c/ProgElem_test/push_swap_tests/lib_maker
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Thu Dec  4 11:12:29 2014 cristopher toozs-hobson
** Last update Thu Mar 12 17:39:40 2015 cristopher toozs-hobson
*/

#include <unistd.h>

void	my_putstr_err(char *str)
{
  int	i;

  i = 0;
  if (str == NULL)
    return ;
  while (str[i] != '\0')
    {
      write(2, &str[i], 1);
      i++;
    }
}
