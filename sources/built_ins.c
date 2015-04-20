/*
** built_ins.c for minishell1 in /home/toozs-_c/Prog_tests/shell1
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Tue Jan 13 09:56:19 2015 cristopher toozs-hobson
** Last update Wed Mar 25 18:16:08 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include "minishell.h"
#include "my.h"

int		special_cd()
{
  int		ret;

  if ((ret = cd_ddot()) == 1)
    return (1);
  else if (ret == 0)
    return (0);
  if ((ret = cd_home()) == 1)
    return (1);
  else if (ret == 0)
    return (0);
  if ((ret = cd_minus()) == 1)
    return (1);
  else if (ret == 0)
    return (0);
  if ((ret = cd_tilde()) == 1)
    return (1);
  else if (ret == 0)
    return (0);
  return (-1);
}

int		cd()
{
  int		ret;
  char		*old_pwd;
  char		*new_path;

  if ((ret = special_cd()) == 0)
    return (0);
  else if (ret == 1)
    return (1);
  if ((chdir(glo.word_tab[1])) == -1)
    {
      my_putstr_err("No such file or directory\n");
      return (1);
    }
  old_pwd = my_str_tab(find_var(glo.env, "PWD"))[1];
  add_env("OLDPWD", old_pwd);
  new_path = remove_slash('.');
  if (my_strcmp(old_pwd, "/") != 0)
    add_env("PWD", my_strcat(old_pwd, my_strcat("/", new_path)));
  else
    add_env("PWD", my_strcat(old_pwd, new_path));
  return (0);
}

int		escape()
{
  exit(0);
}
