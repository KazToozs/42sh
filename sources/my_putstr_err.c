/*
** my_putstr.c for my_putstr in /home/toozs-_c/ProgElem_test/push_swap_tests/lib_maker
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Thu Dec  4 11:12:29 2014 cristopher toozs-hobson
** Last update Mon May 18 15:39:51 2015 cristopher toozs-hobson
*/

#include <unistd.h>
#include "my.h"

void	my_putstr_err(char *str)
{
  if (str == NULL)
    return ;
  write(1, (unsigned char *)str, my_strlen(str));
}
