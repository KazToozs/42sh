/*
** activate_tree.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sat Feb 28 18:55:08 2015 cristopher toozs-hobson
** Last update Mon May 18 14:58:05 2015 cristopher toozs-hobson
*/

#include "minishell.h"

t_exec		exec[]=
  {
    {&semi_colon, ';'},
    {&or_op, 'r'},
    {&and_op, '&'},
    {&pipe_op, '|'},
    {&right_op_check, '>'},
    {&left_op, '<'},
    {&right_op_check, '1'},
    {&double_left_fork, '0'},
    {NULL, 0}
  };

int		launch_tree(t_tree *root, t_main *m)
{
  int		ret;
  int		i;

  i = 0;
  ret = 0;
  while (exec[i].ptr != NULL && root->op != exec[i].op)
    i++;
  if (exec[i].ptr != NULL)
    ret = exec[i].ptr(root, m);
  else
    {
      if ((root->left != NULL) && (root->left->op != '\0'))
        ret = launch_tree(root->left, m);
      if ((root->right != NULL) && (root->right->op != '\0'))
        ret = launch_tree(root->right, m);
      else
	{
	  ret = execute_function(root->exp, m);
	  return (ret);
	}
    }
  return (ret);
}
