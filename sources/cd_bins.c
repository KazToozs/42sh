/*
** cd_bins.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests/sources
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Wed Mar 25 17:45:50 2015 cristopher toozs-hobson
** Last update Thu May 14 12:13:32 2015 cristopher toozs-hobson
*/

#include	<stdlib.h>
#include	<limits.h>
#include	"minishell.h"
#include	"my.h"

int		cd_home(t_main *m)
{
  char		*ret;

  if (!m->word_tab[1] || my_strcmp(m->word_tab[1], "~") == 0)
    {
      if ((ret = env_var_val(glo.env , "HOME", 1)) == NULL)
	return (1);
      if ((chdir(ret)) == -1)
	{
	  free(ret);
	  my_putstr_err("No such file or directory\n");
	  return (1);
	}
      if ((ret = env_var_val(glo.env, "PWD", 1)) == NULL)
	return (1);
      add_env("OLDPWD", ret);
      if ((ret = env_var_val(glo.env, "HOME", 1)) == NULL)
	return (1);
      add_env("PWD", ret);
      return (0);
    }
  return (-1);
}

int		cd_ddot(t_main *m)
{
  char		*new_pwd;
  char		*old_pwd;
  int		i;

  if (my_strcmp(m->word_tab[0], "cd..") == 0
      || my_strcmp(m->word_tab[0], "..") == 0)
    {
      if ((chdir("..")) == -1)
        return (1);
      if ((old_pwd = env_var_val(glo.env, "PWD", 1)) == NULL)
	return (1);
      add_env("OLDPWD", old_pwd);
      i = my_strlen(old_pwd);
      while (i > 1 && old_pwd[i] != '/')
        i--;
      new_pwd = malloc(sizeof(char) * i + 1);
      new_pwd = my_strncpy(new_pwd, old_pwd, i);
      new_pwd[i] = '\0';
      add_env("PWD", new_pwd);
      return (0);
    }
  return (-1);
}

int		cd_minus(t_main *m)
{
  char		*pwd;
  char		*ret;

  if ((ret = env_var_val(glo.env, "PWD", 0)) == NULL)
    return (1);
  pwd = my_strdup(ret);
  if (my_strcmp(m->word_tab[1], "-") == 0)
    {
      if ((ret = env_var_val(glo.env, "OLDPWD", 1)) == NULL)
	return (1);
      if (chdir(ret) == -1)
        {
	  free(ret);
          my_putstr_err("Invalid OLDPWD environement variable\n");
          return (1);
        }
      if ((ret = env_var_val(glo.env, "OLDPWD", 1)) == NULL)
	return (1);
      add_env("PWD", ret);
      add_env("OLDPWD", pwd);
      return (0);
    }
  return (-1);
}

int		cd_tilde(t_main *m)
{
  char		*new_pwd;
  char		*home;
  char		*ret;

  if (m->word_tab[1][0] == '~' && m->word_tab[1][1] == '/')
    {
      if ((ret = env_var_val(glo.env, "HOME", 1)) == NULL)
	return (1);
      home = my_strcat(ret, "/", 0);
      free(ret);
      if (chdir(my_strcat(home, m->word_tab[1] + 2, 0)) == -1)
	{
	  free(home);
	  my_putstr_err("No such file or directory\n");
	  return (1);
	}
      if ((ret = env_var_val(glo.env, "PWD", 1)) == NULL)
	return (1);
      new_pwd = NULL;
      if ((new_pwd = getcwd(new_pwd, PATH_MAX)) == NULL)
	return (1);
      add_env("PWD", new_pwd);
      return (0);
    }
  return (-1);
}
