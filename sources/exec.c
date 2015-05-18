/*
** exec.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Wed Feb 18 16:03:39 2015 cristopher toozs-hobson
** Last update Mon May 18 14:42:43 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include "my.h"
#include "minishell.h"
#include "builtins.h"

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
      free(tab[0]);
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

  if ((my_strcmp(m->word_tab[0], g_bin[i].str)) == 0)
    {
      check = g_bin[i].ptr(m);
      return (check);
    }
  else if ((save = find_function(path, m->word_tab[0])))
    {
      m->word_tab[0] = save;
      check = execute_fork(m->word_tab, glo.env, m);
      return (check);
    }
  else if (m->word_tab)
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
  m->word_tab = my_str_tab(ret);
  path = find_var(glo.env, "PATH");
  while (ret[0] != '\0' && g_bin[i].str != NULL
         && (my_strcmp(m->word_tab[0], g_bin[i].str) != 0))
    i++;
  if ((m->word_tab = globbing(m->word_tab)) == NULL)
    {
      return (1);
    }
  check = execute(path, i, m);
  free_tab(m->word_tab);
  return (check);
}
