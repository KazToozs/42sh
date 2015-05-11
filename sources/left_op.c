/*
** ops_right.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sat Feb 28 19:04:23 2015 cristopher toozs-hobson
** Last update Fri May  8 14:18:57 2015 cristopher toozs-hobson
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include "minishell.h"
#include "my.h"

void		set_file_word(t_tree *root, char ***tab)
{
  char		*tmp;

  if (root->right->exp)
    {
      *tab = my_str_tab(root->right->exp);
      if (*tab && *tab[0])
        {
          tmp = my_strdup(root->right->exp + my_strlen(*tab[0]) + 1);
          root->right->exp = tmp;
        }
    }
}

int		left_prep(t_tree *root)
{
  char		**tab;
  int		fd;

  tab = NULL;
  set_file_word(root, &tab);
  if (tab && !tab[0])
    {
      my_putstr_err("Missing file operand\n");
      return (1);
    }
  if ((fd = open(tab[0], O_RDONLY)) == -1)
    {
      my_putstr_err("No such file or directory lol\n");
      return (1);
    }
  if (dup2(fd, 0) == -1)
    return (1);
  return (0);
}

int		left_exec(t_tree *root, char **check, t_main *m, int in)
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
      if (dup2(in, 0) == -1)
	return (1);
      return (ret);
    }
  else
    {
      ret = execute_function(root->left->exp, m);
      if (dup2(in, 0) == -1)
	return (1);
      return (ret);
    }
  return (0);
}

int		left_op(t_tree *root, t_main *m)
{
  int		stdin_cpy;
  char		**check;

  check = NULL;
  if ((stdin_cpy = dup(0)) == -1)
    return (1);
  if (left_prep(root) == 1)
    return (1);
  if (root->left->exp != NULL)
    check = my_str_tab(root->left->exp);
  return (left_exec(root, check, m, stdin_cpy));
}
