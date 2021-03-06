/*
** main.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Wed Feb  4 15:15:44 2015 cristopher toozs-hobson
** Last update Fri May 22 19:46:00 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "my.h"
#include "minishell.h"

t_glo		g_glo;
extern char	**environ;

char		*put_pwd(char *pwd)
{
  int		count;
  int		i;
  char		*new;

  i = my_strlen(pwd) - 1;
  count = 0;
  while (i >= 0 && count < 2)
    {
      if (pwd[i] == '/')
	count++;
      i--;
    }
  i++;
  new = my_strdup(pwd + i);
  free(pwd);
  return (new);
}

void		display_prompt(int fd)
{
  char		*pwd;

  pwd = NULL;
  g_glo.prompt = NULL;
  if ((pwd = getcwd(pwd, PATH_MAX)) != NULL)
    {
      pwd = put_pwd(pwd);
      pwd = my_strcat("42sh[", pwd, 2);
      pwd = my_strcat(pwd, "]$> ", 1);
      g_glo.prompt = my_strdup(pwd);
    }
  if (g_glo.prompt)
    {
      my_putstr("\e[96m");
      if (fd == 1)
	my_putstr(g_glo.prompt);
      if (fd == 2)
	my_putstr_err(g_glo.prompt);
      my_putstr("\e[39m");
    }
  else
    g_glo.prompt = my_strdup("42sh[<Missing PWD>]$> ");
}

int		start_up(t_main *m)
{
  g_glo.x = 1;
  g_glo.pid = -2;
  m->ret = 0;
  m->file = NULL;
  if (make_env(environ) == 1)
    return (1);
  if ((m->file = init_alias(m)) == NULL)
    return (1);
  if (manage_signal() == 1)
    return (1);
  display_prompt(1);
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
  while ((ret = get_cmd_str()) != NULL)
    {
      if ((check = my_shell(ret, &m)) != -4)
	{
	  free(ret);
	  free_env(g_glo.env);
	  return (check);
	}
      display_prompt(1);
      free(ret);
    }
  my_putstr_err("exit\n");
  return (0);
}
