/*
** status.c for 42sh in /home/toozs-_c/Prog_tests/fourty_two_tests/sources
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Fri May  1 12:01:30 2015 cristopher toozs-hobson
** Last update Fri May  1 16:15:25 2015 cristopher toozs-hobson
*/

#include <signal.h>
#include <sys/wait.h>
#include "minishell.h"
#include "my.h"

t_stat		stat[] =
  {
    {"Hangup", SIGHUP},
    {"Quit", SIGQUIT},
    {"Illegal instruction", SIGILL},
    {"Trace/breakpoint trap", SIGTRAP},
    {"Aborted", SIGABRT},
    {"Aborted", SIGIOT},
    {"Bus error", SIGBUS},
    {"Floating point exception", SIGFPE},
    {"Killed", SIGKILL},
    {"User defined signal 1", SIGUSR1},
    {"Segmentation fault", SIGSEGV},
    {"User defined siganl 2", SIGUSR2},
    {"Alarm clock", SIGALRM},
    {"Terminated", SIGTERM},
    {"Stack fault", SIGSTKFLT},
    {"CPU time limit exceeded", SIGXCPU},
    {"File size limit exceeded", SIGXFSZ},
    {"Virtual timer expired", SIGVTALRM},
    {"Profiling timer expired", SIGPROF},
    {"I/O possible", SIGIO},
    {"I/O possible", SIGPOLL},
    {"Power failure", SIGPWR},
    {"Bad system call", SIGSYS},
    {NULL, 0}
  };

void		status_error(int status)
{
  int		i;

  i = 1;
  while (stat[i].mess != NULL && status != stat[i].sig)
    i++;
  if (stat[i].mess != NULL)
    my_putstr_err(stat[i].mess);
  write(2, "\n", 1);
}

int		status_check(int status, t_main *m)
{
  if (WIFSIGNALED(status))
    {
      status_error(WTERMSIG(status));
      return (m->ret = WTERMSIG(status) + 128);
    }
  if (WIFEXITED(status))
    return (m->ret = WEXITSTATUS(status));
  return (-2);
}
