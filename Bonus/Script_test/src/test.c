/*
** test.c for  in /home/msa_m/Epitech/Systeme_Unix/test/python
** 
** Made by msa_m
** Login   <msa_m@epitech.net>
** 
** Started on  Mon May 11 08:35:43 2015 msa_m
** Last update Thu May 21 11:31:07 2015 msa_m
*/

#include "test.h"

int	init(t_data *d, char *ex)
{
  int	pid;

  d->stdout_cpy = dup(1);
  d->stdin_cpy = dup(0);
  if (access(ex, X_OK) == -1)
    return (my_error("Error: Executable not found\n"));
  if ((name_trace(d)) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (pipe(d->pipefd) == -1)
    return (my_error("Error: Pipe failed\n"));
  if ((pid = fork()) == -1)
    return (my_error("Error: Fork failed\n"));
  return (pid);
}

int	init_son_pipe(t_data *d, char *ex, char **env)
{
  close(d->pipefd[1]);
  dup2(d->pipefd[0], 0);
  dup2(d->fd_file, 1);
  dup2(d->fd_file, 2);
  if (execve(ex, my_str_tab(ex), env) == -1)
    return (my_error("Error: Exec fail\n"));
  return (EXIT_SUCCESS);
}

void	loop_test(t_data *d, int fd)
{
  int	i;
  char	*str;

  i = 1;
  while ((str = get_next_line(fd)) != NULL)
    {
      close(d->pipefd[0]);
      dup2(d->fd_file, 2);
      dup2(d->pipefd[1], 1);
      if (i > 1)
	my_putchar('\n', 2);
      my_putstr("Test number: ", 2);
      my_putnbr(i, 2);
      my_putstr("\n\n", 2);
      my_putstr(str, 1);
      my_putchar('\n', 1);
      if (d->fd_file != 0)
	close(d->fd_file);
      dup2(d->stdout_cpy, 1);
      dup2(d->stdin_cpy, 0);
      i++;
      usleep(500000);
      free(str);
    }
}

int		all_test(char *ex, char **env, char *test)
{
  t_data	d;
  int		pid;
  int		fd;

  d.fd_file = 0;
  if ((fd = open(test, O_RDONLY)) == -1)
    return (my_error("Error: Open failed\n"));
  if ((pid = init(&d, ex)) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (pid == 0)
    {
      if ((init_son_pipe(&d, ex, env)) == EXIT_FAILURE)
	return (EXIT_FAILURE);
    }
  else
    {
      loop_test(&d, fd);
      if (kill(pid, SIGTERM) == -1)
	return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
