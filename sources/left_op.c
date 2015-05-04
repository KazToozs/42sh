/*
** ops_right.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sat Feb 28 19:04:23 2015 cristopher toozs-hobson
** Last update Fri May  1 16:32:37 2015 cristopher toozs-hobson
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "minishell.h"
#include "my.h"

int		left_prep(t_tree *root)
{
  char		**tab;
  int		fd;

  tab = my_str_tab(root->right->exp);
  if (!tab[0])
    {
      my_putstr_err("Missing file operand\n");
      return (1);
    }
  if ((fd = open(tab[0], O_RDONLY)) == -1)
    {
      my_putstr_err("No such file or directory\n");
      return (1);
    }
  if (dup2(fd, 0) == -1)
    return (1);
  return (0);
}

int		left_op(t_tree *root, t_main *m)
{
  int		stdin_cpy;
  int		ret;

  if ((stdin_cpy = dup(0)) == -1)
    return (1);
  if (left_prep(root) == 1)
    return (1);
  if (root->left->exp == NULL)
    {
      ret = launch_tree(root->left, m);
      if (dup2(stdin_cpy, 0) == -1)
	return (1);
      return (ret);
    }
  else
    {
      ret = execute_function(root->left->exp, m);
      if (dup2(stdin_cpy, 0) == -1)
	return (1);
      return (ret);
    }
  return (0);
}
