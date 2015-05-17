/*
** double_left.c for 42sh in /home/toozs-_c/Prog_tests/fourty_two_tests/sources
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Fri May  8 14:02:15 2015 cristopher toozs-hobson
** Last update Sun May 17 10:37:46 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "minishell.h"
#include "my.h"

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
  if ((l.ret = set_file_word(root)) == NULL)
    return (1);
  if (!l.ret[0])
    {
      my_putstr_err("Missing right operand\n");
      return (1);
    }
  my_putstr_err("> ");
  if (dbl_left_read(&l) == 1)
    return (1);
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
      glo.pid = 0;
      glo.x = 2;
      if ((ret = double_left(root, m)) == 1)
        {
          return (ret);
        }
      return (0);
    }
  else
    {
      if (waitpid(pid, &status, 0) == -1)
        return (1);
      pid = 0;
      if ((ret = status_check(status, m)) != -2)
        return (ret);
    }
  return (0);
}
