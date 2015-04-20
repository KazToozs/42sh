/*
** tree.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Tue Feb 17 09:52:57 2015 cristopher toozs-hobson
** Last update Wed Mar 25 19:22:25 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include "minishell.h"
#include "my.h"

t_tree		*make_node(char *data)
{
  t_tree	*new_node;

  if ((new_node = malloc(sizeof(t_tree))) == NULL)
    exit(1);
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

void            free_tree(t_tree *root)
{
  if (root->left != NULL)
    free_tree(root->left);
  if (root->right != NULL)
    free_tree(root->right);
  if (root->left == NULL && root->right == NULL)
    free(root);
}

void		make_tree(t_tree **root, char *ret)
{
  int		i;
  int		check;
  int		fi;

  if (*root == NULL)
    *root = make_node(ret);
  i = my_strlen(ret) - 1;
  if ((fi = check_op(ret)) == 1)
    {
      perform_check(ret, &i, &check, root);
      (*root)->exp = NULL;
      ret[i] = '\0';
      make_tree(&(*root)->left, ret);
      if (check != -1)
	make_tree(&(*root)->right, ret + i + 1);
      else
	make_tree(&(*root)->right, ret + i + 2);
    }
  else if (fi == 0)
    (*root)->exp = ret;
}
