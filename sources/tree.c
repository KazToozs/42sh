/*
** tree.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Tue Feb 17 09:52:57 2015 cristopher toozs-hobson
** Last update Thu May 14 16:19:43 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include "minishell.h"
#include "my.h"

t_tree		*make_node(char *data)
{
  t_tree	*new_node;

  if ((new_node = malloc(sizeof(t_tree))) == NULL)
    return (NULL);
  new_node->exp = data;
  new_node->op = '\0';
  new_node->left = NULL;
  new_node->right = NULL;
  return (new_node);
}

int		quotes(char c, int tru)
{
  int		ret;

  ret = tru;
  if (c == '"' && tru == 0)
    ret = 1;
  else if (c == '"' && tru == 1)
    ret = 0;
  return (ret);
}

void		free_tree(t_tree *root)
{
  if (root->left != NULL)
    free_tree(root->left);
  if (root->right != NULL)
    free_tree(root->right);
  if (root->left == NULL && root->right == NULL)
    free(root);
}

int		set_nodes(t_tree **root, char *ret)
{
  int		i;
  int		fi;
  int		check;

  i = my_strlen(ret) - 1;
  if ((fi = check_op(ret)) == 1)
    {
      if (perform_check(ret, &i, &check, root) == 1)
	return (1);
      (*root)->exp = NULL;
      ret[i] = '\0';
      if (make_tree(&(*root)->left, ret) == 1)
	return (1);
      if (check != -1)
	check = make_tree(&(*root)->right, ret + i + 1);
      else
	check = make_tree(&(*root)->right, ret + i + 2);
      if (check == 1)
	return (1);
    }
  else if (fi == 0)
    (*root)->exp = ret;
  return (0);
}

int		make_tree(t_tree **root, char *ret)
{
  if (*root == NULL)
    if ((*root = make_node(ret)) == NULL)
      {
	my_putstr_err("Malloc error in tree creation\n");
	return (1);
      }
  return (set_nodes(root, ret));
}
