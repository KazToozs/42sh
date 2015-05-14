/*
** group_list.c for 42sh in /home/toozs-_c/Prog_tests/fourty_two_tests/sources
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Fri May  8 15:11:15 2015 cristopher toozs-hobson
** Last update Mon May 11 16:45:53 2015 cristopher toozs-hobson
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <wait.h>
#include "minishell.h"
#include "my.h"

int		show_groups(t_main *m)
{
  t_jobs	*tmp;

  (void)m;//prob?
  tmp = glo.jobs;
  while (glo.jobs != NULL)
    {
      if (glo.jobs->status == 1)
	fprintf(stderr, "[%d] Suspended %s", glo.jobs->nb, glo.jobs->cmd);
      glo.jobs = glo.jobs->next;
    }
  glo.jobs = tmp;
  return (0);
}

void		remove_job(t_jobs **jobs, pid_t gpid)
{
  t_jobs	*start;
  t_jobs	*mark;

  start = (*jobs);
  while ((*jobs) != NULL && (*jobs)->gpid != gpid)
    {
      mark = (*jobs);
      (*jobs) = (*jobs)->next;
    }
  if ((*jobs) == NULL)
    my_putstr_err("Job control error\n");
  else if ((*jobs) == start)
    {
      (*jobs) = NULL;
      free(start);
    }
  else
    {
      mark->next = mark->next->next;
      free((*jobs));
      (*jobs) = start;
    }
}

int		foreground(t_main *m)
{
  t_jobs	*tmp;
  int		ret;
  pid_t		pid;
  int		status;

  tmp = glo.jobs;
  while (glo.jobs && glo.jobs->next != NULL)
    glo.jobs = glo.jobs->next;
  if (glo.jobs)
    {
      if (kill(glo.jobs->gpid, SIGCONT) == -1)
	{
	  glo.jobs = tmp;
	  return (1);
	}
      tcsetpgrp(2, glo.jobs->gpid);
      pid = glo.jobs->gpid;
      glo.jobs = tmp;
      if (waitpid(pid, &status, 0) == -1)
        return (1);
      /* pid = 0; */
      if ((ret = status_check(status, pid, m)) != -2)
        return (ret);
    }
  else
    {
      glo.jobs = tmp;
      fprintf(stderr, "fg: No current job\n");
      return (1);
    }
  return (0);
}

int		add_gpid_end(t_jobs **list, int gpid)
{
  t_jobs	*block;
  t_jobs	*tmp;
  static int	i = 1;

  if ((block = malloc(sizeof(*block))) == NULL)
    return (1);
  block->gpid = gpid;
  block->status = 1;
  tmp = (*list);
  if ((*list) == NULL)
    i = 1;
  while ((*list)->next != NULL)
    {
      (*list) = (*list)->next;
      i++;
    }
  (*list)->next = block;
  block->nb = i;
  (*list) = tmp;
  return (0);
}

// set glo.bg to NULL at start and when no processes are in background.
// waitpid will have to see the status of the process. If stopped, set the
// 'status' gpid structure value to a certain value which the printf can verify
// 
// tcsetpgrp to set the glo.gpid to the new command if the first child process
// (determine by a boolean global variable)
// 
// handle the list when a process is destroyed: free the block and set the
// link of the last block
//
// if stopped, waitpid will return the status. when fg is used, a continue
// signal should be sent and the continued program should be set to the
// foreground and must be waited for again

// do not exit if jobs are alive

// for the background, if the last word in the command is '&', execute the
// command and immediately kill(SIGSTOP) it and place it in the job list
