/*
** ops_left.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sat Feb 28 19:00:11 2015 cristopher toozs-hobson
** Last update Fri May  1 16:34:04 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "my.h"
#include "minishell.h"

int		dbl_left_read(t_left *l)
{
  int		i;

  i = 1;
  while (((l->tab[i - 1] = get_next_line(0)) != NULL)
         && my_strcmp(l->tab[i - 1], l->ret[0]) != 0)
    {
      l->tab[i] = NULL;
      i++;
      if ((l->tab = my_realloc_tab(l->tab, i)) == NULL)
	return (1);
      my_putstr_err("> ");
    }
  if (l->tab[i - 1] == NULL)
    return (0);
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

int		dbl_left_close(t_left *l, t_tree *root, t_main *m)
{
  int		ret;

  if (close(l->pipefd[WRITE_END]) == -1)
    return (1);
  if (dup2(l->out_cpy, WRITE_END) == -1)
    return (1);
  if (root->left->exp == NULL)
    {
      ret = launch_tree(root->left, m);
      if (close(l->pipefd[READ_END]) == -1)
	return (1);
      if (dup2(l->in_cpy, READ_END) == -1)
	return (1);
      return (ret);
    }
  else
    {
      ret = execute_function(root->left->exp, m);
      if (close(l->pipefd[READ_END]) == -1)
	return (1);
      if (dup2(l->in_cpy, READ_END) == -1)
	return (1);
      return (ret);
    }
  return (0);
}

int		double_left(t_tree *root, t_main *m)
{
  t_left	l;
  int		ret;

  l.in_cpy = dup(0);
  l.out_cpy = dup(1);
  if (l.in_cpy == -1 || l.out_cpy == -1)
    return (1);
  if ((l.tab = malloc(sizeof(char *) * 2)) == NULL)
    return (1);
  l.tab[0] = NULL;
  l.ret = my_str_tab(root->right->exp);
  if (!l.ret[0])
    {
      my_putstr_err("Missing right operand\n");
      return (1);
    }
  my_putstr_err("> ");
  ret = dbl_left_read(&l);
  dbl_left_cmp(&l);
  ret = dbl_left_close(&l, root, m);
  return (ret);
}

int		double_left_fork(t_tree *root, t_main *m)
{
  int		status;
  int		ret;
  pid_t		pid;

  if ((pid = fork()) == - 1)
    return (1);
  else if (pid == 0)
    {
      glo.x = 2;
      if ((ret = double_left(root, m)) == 1)
	{
	  return (ret);
	}
      return (1);
    }
  else
    {
      if (waitpid(pid, &status, 0) == -1)
        return (1);
      pid = 0;
    }
  return (0);
}
