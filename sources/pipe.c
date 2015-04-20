/*
** pipe.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sat Feb 28 18:30:03 2015 cristopher toozs-hobson
** Last update Wed Mar  4 13:44:36 2015 cristopher toozs-hobson
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "minishell.h"
#include "my.h"

int		father(int *pipefd, t_tree *root)
{
  if (close(pipefd[WRITE_END]) == -1)
    exit(1);
  if (dup2(pipefd[READ_END], READ_END) == -1)
    exit(1);
  if (root->right->exp == NULL)
    if (root->right->op != '0' && root->right->op != '<')
      launch_tree(root->right);
    else
      {
	my_putstr_err("Ambiguous input redirect\n");
	return (-1);
      }
  else
    execute_function(root->right->exp);
  if (close(READ_END) == -1)
    exit(1);
  wait(0);
  return (0);
}

void		child(int *pipefd, t_tree *root)
{
  if (close(pipefd[READ_END]) == -1)
    exit(1);
  if (dup2(pipefd[WRITE_END], WRITE_END) == -1)
    exit(1);
  if (root->left != NULL)
    launch_tree(root->left);
  exit(0);
}

void            pipe_op(t_tree *root)
{
  int           pipefd[2];
  int           stdin_cpy;
  int           stdout_cpy;

  stdin_cpy = dup(0);
  stdout_cpy = dup(1);
  (stdin_cpy == -1 || stdout_cpy == -1) ? exit(1) : 1;
  (pipe(pipefd) == -1) ? exit(1) : 1;
  ((glo.pid = fork()) == -1) ? exit(1) : 1;
  if (glo.pid == 0)
    child(pipefd, root);
  else
    {
      if (father(pipefd, root) == -1)
	{
	  if (kill(glo.pid, SIGINT) == -1)
	    exit(1);
	}
      if (dup2(stdin_cpy, READ_END) == -1)
        exit(1);
      if (close(pipefd[READ_END]) == -1)
        exit(1);
    }
}
