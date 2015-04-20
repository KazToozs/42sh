/*
** exec.c for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Wed Feb 18 16:03:39 2015 cristopher toozs-hobson
** Last update Thu Apr  2 11:36:01 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include "my.h"
#include "minishell.h"
#include "builtins.h"

char		**add_slash(char **tab)
{
  int		i;
  char		*tmp;

  i = 1;
  while (tab[i] != NULL)
    {
      tmp = tab[i];
      tab[i] = my_strcat(tab[i], "/");
      i++;
      free(tmp);
    }
  return (tab);
}

char		*check_access(char **tab, char *function)
{
  char		*ret;
  int		i;
  char		*tmp;

  i = 1;
  while (tab[i] != NULL)
    {
      tmp = tab[i];
      if (access((ret = my_strcat(tab[i], function)), F_OK) == 0)
      	{
      	  free(tmp);
      	  while (tab[++i] != NULL)
      	    free(tab[i]);
      	  free(tab);
      	  return (ret);
      	}
      free(ret);
      free(tab[i]);
      i++;
    }
  free(tab);
  return (NULL);
}

char		*find_function(char *path, char *function)
{
  char		**tab;
  char		*ret;

  tab = my_str_tab(path);
  tab = add_slash(tab);
  free(tab[0]);
  if (function == NULL)
    return (function);
  if ((ret = check_access(tab, function)) != NULL)
    return (ret);
  else
    return (function);
}

void		execute(char *path, char *ret, int i)
{
  char		*save;

  if ((my_strcmp(glo.word_tab[0], g_bin[i].str)) == 0)
    g_bin[i].ptr();
  else if (path != NULL &&
	   (save = find_function(path, glo.word_tab[0]))
	   != glo.word_tab[0])
    {
      glo.word_tab[0] = save;
      execute_fork(glo.word_tab, glo.env);
    }
  else if (ret[0] != '\0' && g_bin[i].str == NULL)
    my_putstr_err("Unknown command\n");
}

void		execute_function(char *ret)
{
  int		i;
  char		*path;

  i = 0;
  glo.pid = 0;
  glo.word_tab = my_str_tab(ret);
  path = find_var(glo.env, "PATH");
  if (glo.ordtab[0] && glo.word_tab[0][0] == '/')
    {
      my_putstr_err("Unknown command\n");
      free_tab(glo.word_tab);
      return ;
    }
  while (ret[0] != '\0' && g_bin[i].str != NULL
         && (my_strcmp(glo.word_tab[0], g_bin[i].str) != 0))
    i++;
  execute(path, ret, i);
  free_tab(glo.word_tab);
}
