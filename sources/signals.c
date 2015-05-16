/*
** signals.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sat Feb 28 21:44:08 2015 cristopher toozs-hobson
** Last update Fri May 15 17:45:00 2015 cristopher toozs-hobson
*/

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "my.h"

void		send_sig(int non)
{
  (void)non;
  if (glo.pid == 0 && glo.x == 2)
    return ;
  else if (glo.pid == -2)
    {
      my_putstr_err("\n");
      display_prompt(2, glo.env);
    }
}

void		handler(int sig)
{
  if (sig == SIGPIPE)
    {
      if (glo.pid != 0)
	my_putstr_err("Write error: broken pipe\n");
    }
}

int		manage_signal()
{
  if (signal(SIGINT, &send_sig) == SIG_ERR)
    {
      my_putstr_err("Signal error\n");
      return (1);
    }
  else if (signal(SIGPIPE, &handler) == SIG_ERR)
    {
      my_putstr_err("Signal error\n");
      return (1);
    }
  else if (signal(SIGSEGV, &handler) == SIG_ERR)//
    {
      my_putstr_err("Signal error\n");
      return (1);
    }
  return (0);
}
