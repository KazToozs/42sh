/*
** ops_right.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sat Feb 28 19:04:23 2015 cristopher toozs-hobson
** Last update Wed Mar 25 19:23:25 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "minishell.h"
#include "my.h"

char		**right_errors(t_tree *root)
{
  char		**tab;

  if (root->right->exp)
    tab = my_str_tab(root->right->exp);
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

void		right_op(t_tree *root)
{
  int		fd;
  int		stdout_cpy;
  char		**tab;

  if ((stdout_cpy = dup(1)) == -1)
    exit(1);
  if ((tab = right_errors(root)) == NULL)
    return ;
    fd = open(tab[0], O_CREAT | O_WRONLY | O_TRUNC,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd == -1)
    {
      my_putstr_err("Invalid open\n");
      return ;
    }
  if (dup2(fd, 1) == -1)
    exit(1);
  if (root->left->exp == NULL)
    launch_tree(root->left);
  else
    execute_function(root->left->exp);
  if (dup2(stdout_cpy, 1) == -1)
    exit(1);
}

void		double_right(t_tree *root)
{
  int		fd;
  int		stdout_cpy;
  char		**tab;

  if ((stdout_cpy = dup(1)) == -1)
    exit(1);
  tab = my_str_tab(root->right->exp);
  if (!tab[0])
    {
      my_putstr_err("Missing file operand\n");
      return ;
    }
  fd = open(tab[0], O_WRONLY | O_CREAT | O_APPEND,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd == -1)
    {
      my_putstr_err("Invalid open\n");
      return ;
    }
  (dup2(fd, 1) == -1) ? exit(1) : 1;
  (root->left->exp == NULL) ? launch_tree(root->left) :
    execute_function(root->left->exp);
  if (dup2(stdout_cpy, 1) == -1)
    exit(1);
}

void		left_op(t_tree *root)
{
  int		fd;
  int		stdin_cpy;
  char		**tab;

  if ((stdin_cpy = dup(0)) == -1)
    exit(1);
  tab = my_str_tab(root->right->exp);
  if (!tab[0])
    {
      my_putstr_err("Missing file operand\n");
      return ;
    }
  if ((fd = open(tab[0], O_RDONLY)) == -1)
    {
      my_putstr_err("No such file or directory\n");
      return ;
    }
  if (dup2(fd, 0) == -1)
    exit(1);
  if (root->left->exp == NULL)
    launch_tree(root->left);
  else
    execute_function(root->left->exp);
  if (dup2(stdin_cpy, 0) == -1)
    exit(1);
}

void		semi_colon(t_tree *root)
{
  if (root->left)
    launch_tree(root->left);
  if (root->right)
    launch_tree(root->right);
}
