/*
** name_file.c for  in /home/msa_m/Epitech/Systeme_Unix/Bonus/Script_test/src
** 
** Made by msa_m
** Login   <msa_m@epitech.net>
** 
** Started on  Thu May 21 11:21:13 2015 msa_m
** Last update Thu May 21 11:38:09 2015 msa_m
*/

#include "test.h"

int	check_name(t_data *d, char *trace)
{
  char	*conf;

  my_putstr("Are you sure ? The trace already exist.(y\\n)\n", 1);
  if ((conf = get_next_line(0)) == NULL)
      return (EXIT_FAILURE);
  if (conf[0] == 'y' && conf[1] == '\0')
    {
      if ((d->fd_file = open(trace, O_CREAT | O_TRUNC | O_WRONLY,
			     0666)) == -1)
	return (my_error("Error: Open failed\n"));
    }
  else
    {
      free(conf);
      return (EXIT_FAILURE);
    }
  free(conf);
  return (EXIT_SUCCESS);
}

int	name_trace(t_data *d)
{
  char	*trace;

  my_putstr("How you want to call the trace ?\n", 1);
  if ((trace = get_next_line(0)) == NULL)
    return (EXIT_FAILURE);
  if (access(trace, F_OK) == 0)
    {
      if (check_name(d, trace) == EXIT_FAILURE)
	{
	  free(trace);
	  return (EXIT_FAILURE);
	}
    }
  else if ((d->fd_file = open(trace, O_CREAT | O_APPEND | O_WRONLY,
			      0666)) == -1)
    return (my_error("Error: Open failed\n"));
  free(trace);
  return (EXIT_SUCCESS);
}
