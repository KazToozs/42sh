/*
** cd_bins.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests/sources
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Wed Mar 25 17:45:50 2015 cristopher toozs-hobson
** Last update Thu Mar 26 10:11:10 2015 cristopher toozs-hobson
*/

#include	<stdlib.h>
#include	"minishell.h"
#include	"my.h"

int		cd_home()
{
  if (!glo.word_tab[1] || my_strcmp(glo.word_tab[1], "~") == 0)
    {
      if ((find_var(glo.env, "HOME")) != NULL)
        {
          if ((chdir(my_str_tab(find_var(glo.env, "HOME"))[1]) == -1))
            {
              my_putstr_err("No such file or directory\n");
              return (1);
            }
          add_env("OLDPWD", my_str_tab(find_var(glo.env, "PWD"))[1]);
          add_env("PWD", my_str_tab(find_var(glo.env, "HOME"))[1]);
          return (0);
        }
      else
        my_putstr_err("Missing 'HOME' environment variable\n");
      return (1);
    }
  return (-1);
}

int		cd_ddot()
{
  char		*new_pwd;
  char		*old_pwd;
  int		i;

  if (my_strcmp(glo.word_tab[0], "cd..") == 0
      || my_strcmp(glo.word_tab[0], "..") == 0)
    {
      if ((chdir("..")) == -1)
        return (1);
      old_pwd = my_str_tab(find_var(glo.env, "PWD"))[1];
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

int		cd_minus()
{
  char		*pwd;

  pwd = my_str_tab(find_var(glo.env, "PWD"))[1];
  if (my_strcmp(glo.word_tab[1], "-") == 0)
    {
      if ((chdir(my_str_tab(find_var(glo.env, "OLDPWD"))[1]) == -1))
        {
          my_putstr_err("Invlaid OLDPWD environement variable\n");
          return (1);
        }
      add_env("PWD", my_str_tab(find_var(glo.env, "OLDPWD"))[1]);
      add_env("OLDPWD", pwd);
      return (0);
    }
  return (-1);
}

char		*remove_slash(char c)
{
  int		i;

  i = 0;
  while (glo.word_tab[1][i] == c || glo.word_tab[1][i] == '/')
    i++;
  return (glo.word_tab[1] + i);
}

int		cd_tilde()
{
  char		*new_path;
  char		*home;
  char		*ret;

  if (glo.word_tab[1][0] == '~' && glo.word_tab[1][1] == '/')
    {
      if ((ret = find_var(glo.env, "HOME")) != NULL
	  && my_str_tab(ret)[1])
        {
          home = my_strcat(my_str_tab(find_var(glo.env, "HOME"))[1], "/");
          if (chdir(my_strcat(home, glo.word_tab[1] + 2)) == -1)
            {
              my_putstr_err("No such file or directory\n");
              return (1);
            }
          new_path = remove_slash('~');
          add_env("OLDPWD", my_str_tab(find_var(glo.env, "PWD"))[1]);
          add_env("PWD", my_strcat(home, new_path));
          return (0);
        }
      else
        my_putstr_err("Missing 'HOME' environment variable\n");
      return (1);
    }
  return (-1);
}
