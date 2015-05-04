/*
** my_putchar.c for my_putchar in /home/toozs-_c/ProgElem_test/push_swap_tests/lib_maker
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Wed Dec  3 17:05:08 2014 cristopher toozs-hobson
** Last update Fri May  1 17:10:03 2015 cristopher toozs-hobson
*/

#include <unistd.h>

void		my_putchar(char c)
{
  write(1, &c, 1);
}
