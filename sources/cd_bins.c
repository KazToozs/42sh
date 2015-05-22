/*
** cd_bins.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests/sources
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Wed Mar 25 17:45:50 2015 cristopher toozs-hobson
** Last update Fri May 22 19:39:49 2015 cristopher toozs-hobson
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
      if ((ret = env_var_val(g_glo.env , "HOME", 1)) == NULL)
	return (1);
      if ((my_chdir(ret)) == -1)
	{
	  free(ret);
	  return (1);
	}
      ret = env_var_val(g_glo.env, "PWD", 1);
      if (ret != NULL)
	add_env("OLDPWD", ret);
      if ((ret = env_var_val(g_glo.env, "HOME", 1)) == NULL)
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

  old_pwd = NULL;
  if (my_strcmp(m->word_tab[0], "cd..") == 0
      || my_strcmp(m->word_tab[0], "..") == 0)
    {
      if ((my_chdir("..")) == -1)
        return (1);
      if ((old_pwd = env_var_val(g_glo.env, "PWD", 1)) == NULL)
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

  ret = NULL;
  if ((ret = getcwd(ret, PATH_MAX)) == NULL)
    return (1);
  if ((pwd = my_strdup(ret)) == NULL)
    return (1);
  if (my_strcmp(m->word_tab[1], "-") == 0)
    {
      if ((ret = env_var_val(g_glo.env, "OLDPWD", 1)) == NULL)
	return (1);
      if (my_chdir(ret) == -1)
        {
	  free(ret);
          return (1);
        }
      if ((ret = getcwd(ret, PATH_MAX)) == NULL)
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
      if ((ret = env_var_val(g_glo.env, "HOME", 1)) == NULL)
	return (1);
      home = my_strcat(ret, "/", 0);
      free(ret);
      if (my_chdir(my_strcat(home, m->word_tab[1] + 2, 0)) == -1)
	{
	  free(home);
	  return (1);
	}
      if ((ret = env_var_val(g_glo.env, "PWD", 1)) == NULL)
	return (1);
      new_pwd = NULL;
      if ((new_pwd = getcwd(new_pwd, PATH_MAX)) == NULL)
	return (1);
      add_env("PWD", new_pwd);
      add_env("OLDPWD", ret);
      return (0);
    }
  return (-1);
}
