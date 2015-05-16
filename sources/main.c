/*
** main.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Wed Feb  4 15:15:44 2015 cristopher toozs-hobson
** Last update Sat May 16 19:30:41 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "minishell.h"

g_glo		glo;
extern char	**environ;

void		put_pwd(char *pwd, int fd)
{
  int		count;
  int		i;

  i = my_strlen(pwd) - 1;
  count = 0;
  while (i >= 0 && count < 2)
    {
      if (pwd[i] == '/')
	count++;
      i--;
    }
  i++;
  while (pwd[i] != '\0')
    {
      write(fd, &pwd[i], sizeof(char));
      i++;
    }
}

void		display_prompt(int fd, t_env *env)
{
  char		*pwd;

  if (fd == 1)
    {
      if ((pwd = env_var_val(env, "PWD", 0)) != NULL)
      	{
      	  my_putstr("42sh[");
      	  put_pwd(pwd, 1);
	  my_putstr("]$> ");
	}
      else
      	my_putstr("42sh[<Missing PWD>]$> ");
    }
  else if (fd == 2)
    {
      if ((pwd = env_var_val(env, "PWD", 0)) != NULL)
	{
	  my_putstr_err("42sh[");
	  put_pwd(pwd, 2);
	  my_putstr_err("]$> ");
	}
      else
	my_putstr_err("42sh[<Missing PWD>]$> ");
    }
}

int		start_up(t_main *m)
{
  glo.x = 1;
  glo.pid = -2;
  m->ret = 0;
  if (make_env(environ) == 1)
    return (1);
  if (manage_signal() == 1)
    return (1);
  display_prompt(1, glo.env);
  return (0);
}

void		free_env(t_env *env)
{
  t_env		*tmp;

  tmp = env;
  while (env != NULL)
    {
      env = env->next;
      free(tmp);
      tmp = env;
    }
}

int		main()
{
  char		*ret;
  int		check;
  t_main	m;

  if (start_up(&m) == 1)
    return (1);
  while ((ret = get_next_line(0)) != NULL)
    {
      if ((check = my_shell(ret, &m)) != -3)
	{
	  free(ret);
	  free_env(glo.env);
	  return (check);
	}
      display_prompt(1, glo.env);
      free(ret);
    }
  return (0);
}
