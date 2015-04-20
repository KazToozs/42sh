/*
** signals.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sat Feb 28 21:44:08 2015 cristopher toozs-hobson
** Last update Wed Mar  4 14:16:57 2015 cristopher toozs-hobson
*/

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "my.h"

void            send_sig(int non)
{
  (void)non;
  if (glo.pid != 0 && glo.x == 1)
    {
      if (kill(glo.pid, SIGINT) == -1)
        exit (1);
      my_putchar('\n');
    }
  else if (glo.pid == 0 && glo.x == 2)
    exit(0);
  else
    {
      my_putstr_err("\n$>");
    }
}

void            manage_error(char *str)
{
  int           i;

  i = 0;
  while (str[i] != '\0')
    {
      write(2, &str[i], 1);
      i++;
    }
  exit(1);
}

void            manage_signal()
{
  if (signal(SIGINT, &send_sig) == SIG_ERR)
    manage_error("Signal error\n");
}
