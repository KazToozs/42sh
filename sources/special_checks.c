/*
** special_checks.c for 42sh in /home/toozs-_c/Prog_tests/fourty_two_tests/sources
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sun Apr 26 15:30:02 2015 cristopher toozs-hobson
** Last update Mon Apr 27 13:35:45 2015 cristopher toozs-hobson
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

void		redir_set(int *check, t_tree **root, int *i, char set)
{
  if (*check == -1)
    (*root)->op = set;
  else
    *i = *check;
}

int		redir_check(char *ret, int *n, char dir)
{
  int		i;
  int		quote;

  i = my_strlen(ret) - 1;
  quote = 0;
  while (i >= 0)
    {
      quote = quotes(ret[i], quote);
      if (ret[i] == dir && quote == 0)
        {
          if (ret[i] == dir && ret[i - 1] == dir)
            {
              *n = i - 1;
              return (-1);
            }
          return (i);
        }
      i--;
    }
  return (0);
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
