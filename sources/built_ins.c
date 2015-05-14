/*
** built_ins.c for minishell1 in /home/toozs-_c/Prog_tests/shell1
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Tue Jan 13 09:56:19 2015 cristopher toozs-hobson
** Last update Thu May 14 12:08:57 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include <limits.h>
#include "minishell.h"
#include "my.h"

int		special_cd(t_main *m)
{
  int		ret;

  if ((ret = cd_ddot(m)) == 1)
    return (1);
  else if (ret == 0)
    return (0);
  if ((ret = cd_home(m)) == 1)
    return (1);
  else if (ret == 0)
    return (0);
  if ((ret = cd_minus(m)) == 1)
    return (1);
  else if (ret == 0)
    return (0);
  if ((ret = cd_tilde(m)) == 1)
    return (1);
  else if (ret == 0)
    return (0);
  else if (ret == -1)
    return (-1);
  return (1);
}

int		cd(t_main *m)
{
  int		ret;
  char		*old_pwd;
  char		*new_pwd;

  if ((ret = special_cd(m)) == 0)
    return (0);
  else if (ret == 1)
    return (1);
  if ((chdir(m->word_tab[1])) == -1)
    {
      my_putstr_err("No such file or directory\n");
      return (1);
    }
  if ((old_pwd = env_var_val(glo.env, "PWD", 0)) == NULL)
    return (1);
  add_env("OLDPWD", old_pwd);
  new_pwd = NULL;
  if ((new_pwd = getcwd(new_pwd, PATH_MAX)) == NULL)
    return (1);
  add_env("PWD", new_pwd);
  return (0);
}

int		escape_check_nbr(t_main *m)
{
  int		i;

  i = 0;
  while (m->word_tab[1][i] != '\0')
    {
      if (m->word_tab[1][i] < '0' || m->word_tab[1][i] > '9')
	{
	  my_putstr_err("exit: Invalid number\n");
	  return (1);
	}
      i++;
    }
  return (0);
}

int		escape(t_main *m)
{
  int		ret;

  ret = 0;
  m->ret = 0;
  if (m->word_tab[1])
    {
      if (escape_check_nbr(m) == 1)
	return (1);
      ret = my_getnbr(m->word_tab[1]);
      if (ret < 0)
        ret = 256 + ret;
      m->ret = ret;
      return (-3);
    }
  m->ret = ret;
  my_putstr_err("exit\n");
  return (-3);
}
