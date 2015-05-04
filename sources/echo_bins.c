/*
** echo_bins.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Tue Mar  3 14:08:22 2015 cristopher toozs-hobson
** Last update Fri May  1 17:03:43 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include "my.h"
#include "minishell.h"

int		my_echolen(char *str)
{
  int		i;

  i = 0;
  while (str[i] != '\0' && str[i] != '$')
    i++;
  return (i);
}

void		dollar_echo(int i, int *n, t_main *m)
{
  char		*ret;

  if (m->word_tab[i][(*n) + 1] == '?')
    {
      my_put_nbr(m->ret);
      (*n) = (*n) + 1;
    }
  else if ((ret = find_var(m->env, m->word_tab[i] + (*n) + 1))
	   != NULL)
    {
      my_putstr(ret + my_echolen(m->word_tab[i] + (*n) + 1) + 1);
      while (m->word_tab[i][(*n) + 1] != '\0')
	(*n) = (*n) + 1;
    }
}

void		execute_echo(int i, t_main *m)
{
  int		n;

  while (m->word_tab[++i] != NULL)
    {
      n = -1;
      while (m->word_tab[i][++n] != '\0')
        {
          if (m->word_tab[i][n] == '$')
	    dollar_echo(i, &n, m);
          else
            my_putchar(m->word_tab[i][n]);
        }
      if (m->word_tab[i + 1] != NULL)
	my_putchar(' ');
    }
}

int		echo_check_chains(t_main *m)
{
  int		i;
  int		n;

  i = 0;
  while (m->word_tab[++i] != NULL)
    {
      n = -1;
      while (m->word_tab[i][++n] != '\0')
        if (m->word_tab[i][n] == '$')
	  {
	    if (m->word_tab[i][n + 1] == '?')
	      n++;
	    else if (find_var(m->env, m->word_tab[i] + n + 1) == NULL)
	      {
		my_putstr_err(m->word_tab[i] + n + 1);
		my_putstr_err(": Undefined variable\n");
		return (1);
	      }
	  }
    }
  return (0);
}

int		my_echo(t_main *m)
{
  if (echo_check_chains(m) == 1)
    return (1);
  if (my_strcmp(m->word_tab[1], "-n") == 0)
    execute_echo(1, m);
  else
    {
      execute_echo(0, m);
      my_putchar('\n');
    }
  return (0);
}
