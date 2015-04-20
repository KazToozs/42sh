/*
** ops_left.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sat Feb 28 19:00:11 2015 cristopher toozs-hobson
** Last update Sat Feb 28 23:38:18 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "my.h"
#include "minishell.h"

void		dbl_left_read(t_left *l)
{
  int		i;

  i = 1;
  while (((l->tab[i - 1] = get_next_line(0)) != NULL)
         && my_strcmp(l->tab[i - 1], l->ret[0]) != 0)
    {
      l->tab[i] = NULL;
      i++;
      l->tab = my_realloc_tab(l->tab, i);
      my_putstr_err("> ");
    }
  if (l->tab[i - 1] == NULL)
    exit(0);
  l->tab[i] = NULL;
  if (pipe(l->pipefd) == -1)
    exit(1);
  if (dup2(l->pipefd[WRITE_END], WRITE_END) == -1)
    exit(1);
  if (dup2(l->pipefd[READ_END], READ_END) == -1)
    exit(1);
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

void		dbl_left_close(t_left *l, t_tree *root)
{
  if (close(l->pipefd[WRITE_END]) == -1)
    exit(1);
  if (dup2(l->out_cpy, WRITE_END) == -1)
    exit(1);
  if (root->left->exp == NULL)
    launch_tree(root->left);
  else
    execute_function(root->left->exp);
  if (close(l->pipefd[READ_END]) == -1)
    exit(1);
  if (dup2(l->in_cpy, READ_END) == -1)
    exit(1);
}

void		double_left(t_tree *root)
{
  t_left	l;

  l.in_cpy = dup(0);
  l.out_cpy = dup(1);
  if (l.in_cpy == -1 || l.out_cpy == -1)
    exit(1);
  if ((l.tab = malloc(sizeof(char *) * 2)) == NULL)
    exit(1);
  l.tab[0] = NULL;
  l.ret = my_str_tab(root->right->exp);
  if (!l.ret[0])
    {
      my_putstr_err("Missing right operand\n");
      return ;
    }
  my_putstr_err("> ");
  dbl_left_read(&l);
  dbl_left_cmp(&l);
  dbl_left_close(&l, root);
}

void		double_left_fork(t_tree *root)
{
  int		status;

  if ((glo.pid = fork()) == - 1)
    manage_error("Fork failed\n");
  else if (glo.pid == 0)
    {
      glo.x = 2;
      double_left(root);
      exit(0);
    }
  else
    {
      if (waitpid(glo.pid, &status, 0) == -1)
        exit(1);
      glo.pid = 0;
    }
}
