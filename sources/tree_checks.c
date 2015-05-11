/*
** tree_checks.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sat Feb 28 22:09:42 2015 cristopher toozs-hobson
** Last update Fri May  8 12:24:35 2015 cristopher toozs-hobson
*/

#include "minishell.h"
#include "my.h"

int		check_op(char *ret)
{
  int		i;
  int		quote;

  i = my_strlen(ret) - 1;
  quote = 0;
  while (i >= 0)
    {
      quote = quotes(ret[i], quote);
      if ((ret[i] == ';' || ret[i] == '|' || ret[i] == '<'
	   || ret[i] == '>' || (ret[i] == '&' && ret[i - 1] == '&'))
	  && quote == 0)
        return (1);
      i--;
    }
  return (0);
}

int		char_check(char *ret, char c)
{
  int		i;
  int		quote;

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

int		perform_check(char *ret, int *i, int *check, t_tree **root)
{
  if ((*check = char_check(ret, ';')) != 0)
    *i = *check;
  else if ((*check = or_check(ret, i)) != 0)
    {
      if (*check == -1)
        (*root)->op = 'r';
    }
  else if ((*check = and_check(ret, i)) != 0)
    {
      if (*check == -1)
        (*root)->op = '&';
    }
  else if ((*check = char_check(ret, '|')) != 0)
    *i = *check;
  else if ((*check = redir_check(ret, i)) != -2)
    redir_set(check, root, i, ret);
  if (*check != -1 && (ret[*i] == '&' || ret[*i] == '|' || ret[*i] == '>'
		       || ret[*i] == '<' || ret[*i] == ';'))
    (*root)->op = ret[*i];
  else if (*check != -1)
    {
      my_putstr_err("Invalid syntax\n");
      return (1);
    }
  return (0);
}
