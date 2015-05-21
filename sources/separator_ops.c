/*
** separator_ops.c for 42sh in /home/toozs-_c/Prog_tests/fourty_two_tests/sources
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sat Apr 25 16:12:02 2015 cristopher toozs-hobson
** Last update Thu May 21 11:39:49 2015 cristopher toozs-hobson
*/

#include <sys/types.h>
#include <sys/wait.h>
#include "minishell.h"
#include "my.h"

int		sep_fork()
{
  if ((glo.pid = fork()) == - 1)
    {
      my_putstr_err("Fork failed\n");
      return (1);
    }
  return (0);
}

int		semi_colon(t_tree *root, t_main *m)
{
  int		ret;

  if (root->left)
    {
      ret = launch_tree(root->left, m);
    }
  if (root->right && glo.pid == -1)
    {
      ret = launch_tree(root->right, m);
      return (ret);
    }
  return (ret);
}

int		and_op(t_tree *root, t_main *m)
{
  int		ret;

  if (root->left)
    ret = launch_tree(root->left, m);
  if (root->right && ret == 0 && glo.pid == -1)
    {
      if ((ret = launch_tree(root->right, m)) != 0)
        return (ret);
    }
  return (ret);
}

int		or_op(t_tree *root, t_main *m)
{
  int		ret;

  if (root->left)
    ret = launch_tree(root->left, m);
  if (root->right && ret != 0)
    ret = launch_tree(root->right, m);
  return (ret);
}
