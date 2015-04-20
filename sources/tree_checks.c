/*
** tree_checks.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sat Feb 28 22:09:42 2015 cristopher toozs-hobson
** Last update Sat Feb 28 22:17:09 2015 cristopher toozs-hobson
*/

#include <unistd.h>
#include "minishell.h"
#include "my.h"

int             check_op(char *ret)
{
  int           i;
  int           quote;

  i = my_strlen(ret) - 1;
  quote = 0;
  while (i >= 0)
    {
      quote = quotes(ret[i], quote);
      if ((ret[i] == ';' || ret[i] == '|' || ret[i] == '<'
	   || ret[i] == '>') && quote == 0)
        return (1);
      i--;
    }
  return (0);
}

int             char_check(char *ret, char c)
{
  int           i;
  int           quote;

  i = my_strlen(ret) - 1;
  quote = 0;
  while (i >= 0)
    {
      quote = quotes(ret[i], quote);
      if (ret[i] == c && quote == 0)
        return (i);
      i--;
    }
  return (0);
}

int             right_check(char *ret, int *n)
{
  int           i;
  int           quote;

  i = my_strlen(ret) - 1;
  quote = 0;
  while (i >= 0)
    {
      quote = quotes(ret[i], quote);
      if (ret[i] == '>' && quote == 0)
        {
          if (ret[i] == '>' && ret[i - 1] == '>')
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

int             left_check(char *ret, int *n)
{
  int           i;
  int           quote;

  i = my_strlen(ret) - 1;
  quote = 0;
  while (i >= 0)
    {
      quote = quotes(ret[i], quote);
      if (ret[i] == '<' && quote == 0)
        {
          if (ret[i] == '<' && ret[i - 1] == '<')
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

void            perform_check(char *ret, int *i, int *check, t_tree **root)
{
  if ((*check = char_check(ret, ';')) != 0)
    *i = *check;
  else if ((*check = right_check(ret, i)) != 0)
    {
      if (*check == -1)
        (*root)->op = '1';
      else
        *i = *check;
    }
  else if ((*check = char_check(ret, '|')) != 0)
    *i = *check;
  else if ((*check = left_check(ret, i)) != 0)
    {
      if (*check == -1)
        (*root)->op = '0';
      else
        *i = *check;
    }
  if (*check != -1)
    (*root)->op = ret[*i];
}
