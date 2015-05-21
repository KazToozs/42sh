/*
** main.c for  in /home/msa_m/Epitech/Systeme_Unix/test/python/projet_en_c/src
** 
** Made by msa_m
** Login   <msa_m@epitech.net>
** 
** Started on  Fri May 15 15:35:32 2015 msa_m
** Last update Tue May 19 13:49:44 2015 msa_m
*/

#include "test.h"

int	main(int ac, char **av, char **env)
{
  if (ac == 3)
    {
      if ((all_test(av[1], env, av[2])) == EXIT_SUCCESS)
	return (EXIT_SUCCESS);
    }
  else
    my_putstr("Usage: ./script [shell] [test]", 2);
  my_putchar('\n', 1);
  return (EXIT_FAILURE);
}
