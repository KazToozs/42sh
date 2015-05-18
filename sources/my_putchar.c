/*
** my_putchar.c for my_putchar in /home/toozs-_c/ProgElem_test/push_swap_tests/lib_maker
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Wed Dec  3 17:05:08 2014 cristopher toozs-hobson
** Last update Mon May 18 14:38:40 2015 cristopher toozs-hobson
*/

#include <unistd.h>

void		my_putchar(char c)
{
  unsigned char	d;

  d = (unsigned char)c;
  write(1, &d, 1);
}
