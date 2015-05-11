/*
** special_checks.c for 42sh in /home/toozs-_c/Prog_tests/fourty_two_tests/sources
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sun Apr 26 15:30:02 2015 cristopher toozs-hobson
** Last update Fri May  8 12:24:30 2015 cristopher toozs-hobson
*/

#include "minishell.h"
#include "my.h"

int		and_check(char *ret, int *n)
{
  int		i;
  int		quote;

  i = my_strlen(ret) - 1;
  quote = 0;
  while (i >= 0)
    {
      quote = quotes(ret[i], quote);
      if (ret[i] == '&' && ret[i - 1] == '&')
        {
          *n = i - 1;
          return (-1);
        }
      i--;
    }
  return (0);
}

void		redir_set(int *check, t_tree **root, int *i, char *ret)
{
  if (*check == -1)
    {
      if (ret[*i] == '>')
	(*root)->op = '1';
      else if (ret[*i] == '<')
	(*root)->op = '0';
    }
  else
    *i = *check;
}

int		redir_check(char *ret, int *n)
{
  int		i;
  int		quote;

  i = my_strlen(ret) - 1;
  quote = 0;
  while (i >= 0)
    {
      quote = quotes(ret[i], quote);
      if ((ret[i] == '<' || ret[i] == '>') && quote == 0)
        {
          if ((i - 1 >= 0) && ((ret[i] == '<' && ret[i - 1] == '<')
			       || (ret[i] == '>' && ret[i - 1] == '>')))
            {
              *n = i - 1;
              return (-1);
            }
          return (i);
        }
      i--;
    }
  return (-2);
}

int		or_check(char *ret, int *n)
{
  int		i;
  int		quote;

  i = my_strlen(ret) - 1;
  quote = 0;
  while (i >= 0)
    {
      quote = quotes(ret[i], quote);
      if (ret[i] == '|' && ret[i - 1] == '|')
        {
          *n = i - 1;
          return (-1);
        }
      i--;
    }
  return (0);
}
