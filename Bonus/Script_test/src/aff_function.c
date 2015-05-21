/*
** aff_function.c for  in /home/msa_m/Epitech/Systeme_Unix/test/python/projet_en_c/src
** 
** Made by msa_m
** Login   <msa_m@epitech.net>
** 
** Started on  Fri May 15 11:42:26 2015 msa_m
** Last update Tue May 19 13:01:41 2015 msa_m
*/

#include "test.h"

void	my_putchar(char n, int fd)
{
  write(fd, &n, 1);
}

void	my_putstr(char *str, int fd)
{
  int	i;

  i = 0;
  while (str[i])
    my_putchar(str[i++], fd);
}

void		my_putnbr(int nb, int fd)
{
  int		div;

  if (nb < 0)
    {
      nb = (-1) * nb;
      my_putchar('-', fd);
      my_putchar(nb, fd);
    }
  div = 1;
  while (nb / div > 9)
    div = div * 10;
  while (div != 0)
    {
      my_putchar('0' + (nb / div) % 10, fd);
      nb = nb % div;
      div = div / 10;
    }
}

int	my_error(char *str)
{
  my_putstr(str, 2);
  return (EXIT_FAILURE);
}
