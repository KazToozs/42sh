/*
** pipe.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sat Feb 28 18:30:03 2015 cristopher toozs-hobson
** Last update Fri May  1 16:28:30 2015 cristopher toozs-hobson
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "minishell.h"
#include "my.h"

int		father_right(t_tree *root, t_main *m)
{
  int		check;

  if (root->right->op != '0' && root->right->op != '<')
    {
      check = launch_tree(root->right, m);
      return (check);
    }
  else
    {
      my_putstr_err("Ambiguous input redirect\n");
      return (1);
    }
  return (0);
}

int		father(int *pipefd, t_tree *root, pid_t pid, t_main *m)
{
  int		check;
  int		status;

  if (close(pipefd[WRITE_END]) == -1)
    return (1);
  if (dup2(pipefd[READ_END], READ_END) == -1)
    return (1);
  if (root->right->exp == NULL)
    check = father_right(root, m);
  else
    check = execute_function(root->right->exp, m);
  if (close(READ_END) == -1)
    return (1);
  if (waitpid(pid, &status, 0) == -1)
    return (1);
  if (WIFSIGNALED(status))
    {
      status_error(WTERMSIG(status));
      return (m->ret = WTERMSIG(status) + 128);
    }
  if (WIFEXITED(status))
    return (m->ret = WEXITSTATUS(status));
  return (check);
}

int		child(int *pipefd, t_tree *root, t_main *m)
{
  glo.pid = 0;
  if (close(pipefd[READ_END]) == -1)
    return (1);
  if (dup2(pipefd[WRITE_END], WRITE_END) == -1)
    return (1);
  if (root->left != NULL)
    return (launch_tree(root->left, m));
  return (0);
}

int		execute_pipe(t_pipe *p, t_tree *root, pid_t pid, t_main *m)
{
  if (pid == 0)
    return (child(p->pipefd, root, m));
  else
    {
      p->check = father(p->pipefd, root, pid, m);
      if (dup2(p->in_cpy, READ_END) == -1)
        return (1);
      if (close(p->pipefd[READ_END]) == -1)
        return (1);
      return (p->check);
    }
}

int		pipe_op(t_tree *root, t_main *m)
{
  t_pipe	p;
  pid_t		pid;

  p.in_cpy = dup(0);
  p.out_cpy = dup(1);
  if (p.in_cpy == -1 || p.out_cpy == -1)
    return (1);
  if (pipe(p.pipefd) == -1)
    return (1);
  if ((pid = fork()) == -1)
    return (1);
  return (execute_pipe(&p, root, pid, m));
}
