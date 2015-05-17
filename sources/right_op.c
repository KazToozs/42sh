/*
** right_op.c for 42sh in /home/toozs-_c/Prog_tests/fourty_two_tests/sources
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sat Apr 25 16:09:43 2015 cristopher toozs-hobson
** Last update Sun May 17 12:38:53 2015 cristopher toozs-hobson
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include "minishell.h"
#include "my.h"

int		right_op_check(t_tree *root, t_main *m)
{
  int		ret;

  ret = 1;
  if (root->op == '>')
    ret = right_op(root, 1, m);
  else if (root->op == '1')
    ret = right_op(root, 2, m);
  return (ret);
}

char		**right_errors(t_tree *root)
{
  char		**tab;

  if (root->right->exp)
    {
      if ((tab = set_file_word(root)) == NULL)
	return (NULL);
    }
  else
    {
      my_putstr_err("Invalid syntax\n");
      return (NULL);
    }
  if (!tab[0])
    {
      my_putstr_err("Missing file operand\n");
      return (NULL);
    }
  else
    return (tab);
}

int		right_prep(t_tree *root, int type)
{
  int		fd;
  char		**tab;

  if ((tab = right_errors(root)) == NULL)
    return (1);
  if (type == 1)
    fd = open(tab[0], O_CREAT | O_WRONLY | O_TRUNC,
              S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  else if (type == 2)
    fd = open(tab[0], O_WRONLY | O_CREAT | O_APPEND,
              S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd == -1)
    {
      my_putstr_err("Invalid open\n");
      return (1);
    }
  if (dup2(fd, 1) == -1)
    return (1);
  return (0);
}

int		execute_right(t_tree *root, t_main *m, char **check, int out)
{
  int		ret;

  if ((!root->left->exp && root->left->op)
      || (root->left->exp && check && !check[0]))
    {
      free_tab(check);
      if (!root->left->op)
	ret = execute_function(root->right->exp, m);
      else
	ret = launch_tree(root->left, m);
      if (dup2(out, 1) == -1)
        return (1);
      return (ret);
    }
  else
    {
      ret = execute_function(root->left->exp, m);
      if (dup2(out, 1) == -1)
        return (1);
      return (ret);
    }
  return (0);
}

int		right_op(t_tree *root, int type, t_main *m)
{
  int		stdout_cpy;
  char		**check;

  check = NULL;
  if ((stdout_cpy = dup(1)) == -1)
    return (1);
  if (right_prep(root, type) == 1)
    return (1);
  if (root->left->exp != NULL)
    check = my_str_tab(root->left->exp);
  return (execute_right(root, m, check, stdout_cpy));
}
