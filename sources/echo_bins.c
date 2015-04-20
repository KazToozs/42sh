/*
** echo_bins.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Tue Mar  3 14:08:22 2015 cristopher toozs-hobson
** Last update Tue Mar  3 14:18:19 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include "my.h"
#include "minishell.h"

void		execute_echo(int i)
{
  int		n;
  char		*ret;

  while (glo.word_tab[++i] != NULL)
    {
      n = -1;
      while (glo.word_tab[i][++n] != '\0')
        {
          if (glo.word_tab[i][n] == '$')
            {
              if ((ret = find_var(glo.env, glo.word_tab[i] + n + 1)) != NULL)
                {
                  my_putstr(ret + my_strlen(glo.word_tab[i] + n + 1) + 1);
                  while (glo.word_tab[i][n + 1] != '\0')
                    n++;
                }
            }
          else
            my_putchar(glo.word_tab[i][n]);
        }
      my_putchar(' ');
    }
}

void		echo(int mode)
{
  int		i;

  if (mode == 1)
    i = 0;
  else
    i = 1;
  execute_echo(i);
  if (mode == 1)
    my_putchar('\n');
}

int		echo_check_chains()
{
  int		i;
  int		n;

  i = 0;
  while (glo.word_tab[++i] != NULL)
    {
      n = -1;
      while (glo.word_tab[i][++n] != '\0')
        if (glo.word_tab[i][n] == '$')
          if (find_var(glo.env, glo.word_tab[i] + n + 1) == NULL)
            {
              my_putstr_err(glo.word_tab[i] + n + 1);
              my_putstr_err(": Undefined variable\n");
              return (1);
            }
    }
  return (0);
}

int		my_echo()
{
  if (echo_check_chains() == 1)
    return (1);
  if (my_strcmp(glo.word_tab[1], "-n") == 0)
    echo(0);
  else
    echo(1);
  return (0);
}
