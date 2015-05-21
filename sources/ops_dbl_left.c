/*
** ops_left.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sat Feb 28 19:00:11 2015 cristopher toozs-hobson
** Last update Thu May 21 13:13:54 2015 cristopher toozs-hobson
*/

#include "my.h"
#include "minishell.h"

int		dbl_left_read(t_left *l)
{
  int		i;

  i = 1;
  while (((l->tab[i - 1] = get_cmd_str()) != NULL)
         && my_strcmp(l->tab[i - 1], l->ret[0]) != 0)
    {
      l->tab[i] = NULL;
      i++;
      if ((l->tab = my_realloc_tab(l->tab, i)) == NULL)
	return (1);
      my_putstr_in("> ");
    }
  if (l->tab[i - 1] == NULL)
    return (1);
  l->tab[i] = NULL;
  if (pipe(l->pipefd) == -1)
    return (1);
  if (dup2(l->pipefd[WRITE_END], WRITE_END) == -1)
    return (1);
  if (dup2(l->pipefd[READ_END], READ_END) == -1)
    return (1);
  return (0);
}

void		dbl_left_cmp(t_left *l)
{
  int		i;

  i = 0;
  while (my_strcmp(l->tab[i], l->ret[0]) != 0)
    {
      my_putstr(l->tab[i]);
      my_putchar('\n');
      i++;
    }
  free_tab(l->ret);
}

int		dbl_left_exec(t_left *l, t_tree *rt, t_main *m, char **ch)
{
  int		ret;

  if ((!rt->left->exp && rt->left->op) || (rt->left->exp && ch && !ch[0]))
    {
      free_tab(ch);
      if (!rt->left->op)
	ret = execute_function(rt->right->exp, m);
      else
	ret = launch_tree(rt->left, m);
      if (close(l->pipefd[READ_END]) == -1)
	return (1);
      if (dup2(l->in_cpy, READ_END) == -1)
	return (1);
      return (ret);
    }
  else
    {
      ret = execute_function(rt->left->exp, m);
      if (close(l->pipefd[READ_END]) == -1)
	return (1);
      if (dup2(l->in_cpy, READ_END) == -1)
	return (1);
      return (ret);
    }
  return (0);
}

int		dbl_left_close(t_left *l, t_tree *root, t_main *m)
{
  char		**check;

  check = NULL;
  if (close(l->pipefd[WRITE_END]) == -1)
    return (1);
  if (dup2(l->out_cpy, WRITE_END) == -1)
    return (1);
  if (root->left->exp != NULL)
    check = my_str_tab(root->left->exp);
  return (dbl_left_exec(l, root, m, check));
}
