/*
** cd_bins.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests/sources
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Wed Mar 25 17:45:50 2015 cristopher toozs-hobson
** Last update Fri May  1 16:09:39 2015 cristopher toozs-hobson
*/

#include	<stdlib.h>
#include	"minishell.h"
#include	"my.h"

int		cd_home(t_main *m)
{
  if (!m->word_tab[1] || my_strcmp(m->word_tab[1], "~") == 0)
    {
      if ((find_var(m->env, "HOME")) != NULL)
        {
          if ((chdir(my_str_tab(find_var(m->env, "HOME"))[1]) == -1))
            {
              my_putstr_err("No such file or directory\n");
              return (1);
            }
          add_env("OLDPWD", my_str_tab(find_var(m->env, "PWD"))[1], m);
          add_env("PWD", my_str_tab(find_var(m->env, "HOME"))[1], m);
          return (0);
        }
      else
        my_putstr_err("Missing 'HOME' environment variable\n");
      return (1);
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
      old_pwd = my_str_tab(find_var(m->env, "PWD"))[1];
      add_env("OLDPWD", old_pwd, m);
      i = my_strlen(old_pwd);
      while (i > 1 && old_pwd[i] != '/')
        i--;
      new_pwd = malloc(sizeof(char) * i + 1);
      new_pwd = my_strncpy(new_pwd, old_pwd, i);
      new_pwd[i] = '\0';
      add_env("PWD", new_pwd, m);
      return (0);
    }
  return (-1);
}

int		cd_minus(t_main *m)
{
  char		*pwd;

  pwd = my_str_tab(find_var(m->env, "PWD"))[1];
  if (my_strcmp(m->word_tab[1], "-") == 0)
    {
      if ((chdir(my_str_tab(find_var(m->env, "OLDPWD"))[1]) == -1))
        {
          my_putstr_err("Invlaid OLDPWD environement variable\n");
          return (1);
        }
      add_env("PWD", my_str_tab(find_var(m->env, "OLDPWD"))[1], m);
      add_env("OLDPWD", pwd, m);
      return (0);
    }
  return (-1);
}

char		*remove_slash(char c, t_main *m)
{
  int		i;

  i = 0;
  while (m->word_tab[1][i] == c || m->word_tab[1][i] == '/')
    i++;
  return (m->word_tab[1] + i);
}

int		cd_tilde(t_main *m)
{
  char		*new_path;
  char		*home;
  char		*ret;

  if (m->word_tab[1][0] == '~' && m->word_tab[1][1] == '/')
    {
      if ((ret = find_var(m->env, "HOME")) != NULL
	  && my_str_tab(ret)[1])
        {
          home = my_strcat(my_str_tab(find_var(m->env, "HOME"))[1], "/");
          if (chdir(my_strcat(home, m->word_tab[1] + 2)) == -1)
            {
              my_putstr_err("No such file or directory\n");
              return (1);
            }
          new_path = remove_slash('~', m);
          add_env("OLDPWD", my_str_tab(find_var(m->env, "PWD"))[1], m);
          add_env("PWD", my_strcat(home, new_path), m);
          return (0);
        }
      else
        my_putstr_err("Missing 'HOME' environment variable\n");
      return (1);
    }
  return (-1);
}
