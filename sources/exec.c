/*
** exec.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Wed Feb 18 16:03:39 2015 cristopher toozs-hobson
** Last update Fri May 22 19:41:17 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include "my.h"
#include "minishell.h"

t_bins		bin[] =
  {
    {&escape, "exit"},
    {&cd, "cd"},
    {&cd, "cd.."},
    {&cd, ".."},
    {&remove_env_var, "unsetenv"},
    {&my_setenv, "setenv"},
    {&display_env, "env"},
    {&my_echo, "echo"},
    {&built_source, "source"},
    {&built_alias, "alias"},
    {&built_export, "export"},
    {NULL, NULL}
  };

char		**add_slash(char **tab)
{
  int		i;

  i = 1;
  while (tab[i] != NULL)
    {
      tab[i] = my_strcat(tab[i], "/", 1);
      i++;
    }
  return (tab);
}

char		*find_function(char *path, char *function)
{
  char		**tab;
  char		*ret;

  tab = NULL;
  if (path)
    {
      tab = my_str_tab(path);
      tab = add_slash(tab);
    }
  if (function == NULL)
    return (function);
  ret = check_access(tab, function);
  return (ret);
}

int		execute(char *path, int i, t_main *m)
{
  char		*save;
  int		check;

  if ((my_strcmp(m->word_tab[0], bin[i].str)) == 0)
    {
      check = bin[i].ptr(m);
      return (check);
    }
  else if ((save = find_function(path, m->word_tab[0])))
    {
      m->word_tab[0] = save;
      check = execute_fork(m->word_tab, g_glo.env, m);
      return (check);
    }
  else if (m->word_tab && m->word_tab[0])
    {
      my_putstr_err("Unknown command\n");
      return (1);
    }
  return (0);
}

int		execute_function(char *ret, t_main *m)
{
  int		i;
  char		*path;
  int		check;

  i = 0;
  if (ret && ret[0])
    {
      if ((m->file->exp = my_strdup(ret)) == NULL)
	return (1);
      if ((ret = alias(ret, m->file)) == NULL)
	return (1);
      m->word_tab = my_str_tab(ret);
      path = find_var(g_glo.env, "PATH");
      while (ret[0] != '\0' && bin[i].str != NULL
	     && (my_strcmp(m->word_tab[0], bin[i].str) != 0))
	i++;
      if ((m->word_tab = globbing(m->word_tab)) == NULL)
	{
	  return (1);
	}
      check = execute(path, i, m);
      free_tab(m->word_tab);
      return (check);
    }
  return (1);
}
