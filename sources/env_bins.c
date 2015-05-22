/*
** env_bins.c for minishell1 in /home/toozs-_c/Prog_tests/shell1/first_try
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sat Jan 31 00:30:58 2015 cristopher toozs-hobson
** Last update Fri May 22 19:38:19 2015 cristopher toozs-hobson
*/

#include "minishell.h"
#include "my.h"

void		create_env_var(char *value, char *var, t_env **tmp)
{
  char		*new;
  char		**tab;

  if (g_glo.env != NULL)
    {
      new = my_strcat((tab = my_str_tab(g_glo.env->var))[0], "=", 0);
      new = my_strcat(new, value, 1);
      free_tab(tab);
      g_glo.env->var = new;
    }
  else
    {
      g_glo.env = *tmp;
      new = my_strcat(var, "=", 0);
      new = my_strcat(new, value, 1);
      my_put_in_list_end(&g_glo.env, new, tmp);
    }
}

void		add_env(char *var, char *value)
{
  t_env		*tmp;
  char		**tab;

  tmp = g_glo.env;
  while (g_glo.env != NULL
	 && (my_strcmp(var, (tab = my_str_tab(g_glo.env->var))[0]) != 0))
    {
      free_tab(tab);
      g_glo.env = g_glo.env->next;
    }
  create_env_var(value, var, &tmp);
  g_glo.env = tmp;
}

int		my_setenv(t_main *m)
{
  if (m->word_tab[1] != NULL)
    add_env(m->word_tab[1], m->word_tab[2]);
  else
    {
      my_putstr_err("Missing argument. Use: setenv [-var] [-value]\n");
      return (1);
    }
  return (0);
}

int		display_env()
{
  if (g_glo.env != NULL)
    my_show_list(g_glo.env);
  else
    my_putstr_err("No environment variables to display\n");
  return (0);
}

int		remove_env_var(t_main *m)
{
  t_env		*tmp;

  tmp = g_glo.env;
  if (!m->word_tab[1])
    {
      my_putstr_err("Missing argument. Use: unsetenv [-var]\n");
      return (1);
    }
  while (g_glo.env != NULL &&
         (my_strcmp(m->word_tab[1], my_str_tab(g_glo.env->var)[0]) != 0))
    g_glo.env = g_glo.env->next;
  if (g_glo.env == NULL)
    {
      my_putstr_err("Invalid variable: use 'env' command to find variables\n");
      g_glo.env = tmp;
      return (1);
    }
  else if (my_strcmp(m->word_tab[1], my_str_tab(g_glo.env->var)[0]) == 0)
    remove_node(&g_glo.env, &tmp);
  g_glo.env = tmp;
  return (0);
}
