/*
** tree_checks.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sat Feb 28 22:09:42 2015 cristopher toozs-hobson
** Last update Sat May 16 17:29:08 2015 cristopher toozs-hobson
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
  if ((*check = separator_checks(ret, i)) != -2)
    {
      if (*check == -1)
	{
	  if (ret[*i] == '&')
	    (*root)->op = '&';
	  if (ret[*i] == '|')
	    (*root)->op = 'r';
	}
      else
	*i = *check;
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
