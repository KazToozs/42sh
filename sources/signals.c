/*
** signals.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sat Feb 28 21:44:08 2015 cristopher toozs-hobson
** Last update Fri May 22 19:42:19 2015 cristopher toozs-hobson
*/

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "my.h"

void		handler(int sig)
{
  if (sig == SIGPIPE)
    {
      if (g_glo.pid != 0)
	my_putstr_err("Write error: broken pipe\n");
    }
  if (sig == SIGINT)
    {
      if (g_glo.pid == 0 && g_glo.x == 2)
	return ;
      else if (g_glo.pid == -2)
	{
	  my_putstr_err("\n");
	  display_prompt(2);
	  init_arg();
	}
    }
}

int		manage_signal()
{
  if (signal(SIGINT, &handler) == SIG_ERR)
    {
      my_putstr_err("Signal error\n");
      return (1);
    }
  else if (signal(SIGPIPE, &handler) == SIG_ERR)
    {
      my_putstr_err("Signal error\n");
      return (1);
    }
  else if (signal(SIGSEGV, &handler) == SIG_ERR)
    {
      my_putstr_err("Signal error\n");
      return (1);
    }
  return (0);
}
