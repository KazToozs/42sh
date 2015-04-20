/*
** activate_tree.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sat Feb 28 18:55:08 2015 cristopher toozs-hobson
** Last update Wed Mar 25 19:23:13 2015 cristopher toozs-hobson
*/

#include "minishell.h"

void		execute_tree(t_tree *root, char op)
{
  if (op == ';')
    semi_colon(root);
  else if (op == '|')
    pipe_op(root);
  else if (op == '>')
    right_op(root);
  else if (op == '<')
    left_op(root);
  else if (op == '1')
    double_right(root);
  else if (op == '0')
    double_left_fork(root);
}

void		launch_tree(t_tree *root)
{
  if (root->op == ';')
    execute_tree(root, ';');
  else if (root->op == '>')
    execute_tree(root, '>');
  else if (root->op == '1')
    execute_tree(root, '1');
  else if (root->op == '|')
    execute_tree(root, '|');
  else
    {
      if ((root->left != NULL) && (root->left->op != '\0'))
        launch_tree(root->left);
      if ((root->right != NULL) && (root->right->op != '\0'))
        launch_tree(root->right);
      if ((root->left != NULL) && (root->right != NULL))
        execute_tree(root, root->op);
      else
        execute_function(root->exp);
    }
}
