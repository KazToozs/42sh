/*
** env_bins.c for minishell1 in /home/toozs-_c/Prog_tests/shell1/first_try
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sat Jan 31 00:30:58 2015 cristopher toozs-hobson
** Last update Fri May  1 16:49:46 2015 cristopher toozs-hobson
*/

#include "minishell.h"
#include "my.h"

void		create_env_var(char *value, char *var, t_env *tmp, t_main *m)
{
  char		*new;
  char		**tab;

  if (m->env != NULL)
    {
      new = my_strcat((tab = my_str_tab(m->env->var))[0], "=");
      new = my_strcat(new, value);
      free_tab(tab);
      m->env->var = new;
    }
  else
    {
      m->env = tmp;
      new = my_strcat(var, "=");
      new = my_strcat(new, value);
      my_put_in_list_end(&m->env, new, &tmp);
    }
}

void		add_env(char *var, char *value, t_main *m)
{
  t_env		*tmp;
  char		**tab;

  tmp = m->env;
  while (m->env != NULL
	 && (my_strcmp(var, (tab = my_str_tab(m->env->var))[0]) != 0))
    {
      free_tab(tab);
      m->env = m->env->next;
    }
  create_env_var(value, var, tmp, m);
  m->env = tmp;
}

int		my_setenv(t_main *m)
{
  if (m->word_tab[1] != NULL)
    add_env(m->word_tab[1], m->word_tab[2], m);
  else
    {
      my_putstr_err("Missing argument. Use: setenv [-var] [-value]\n");
      return (1);
    }
  return (0);
}

int		display_env(t_main *m)
{
  if (m->env != NULL)
    my_show_list(m->env);
  else
    my_putstr_err("No environment variables to display\n");
  return (0);
}

int		remove_env_var(t_main *m)
{
  t_env		*tmp;

  tmp = m->env;
  if (!m->word_tab[1])
    {
      my_putstr_err("Missing argument. Use: unsetenv [-var]\n");
      return (1);
    }
  while (m->env != NULL &&
         (my_strcmp(m->word_tab[1], my_str_tab(m->env->var)[0]) != 0))
    m->env = m->env->next;
  if (m->env == NULL)
    {
      my_putstr_err("Invalid variable: use 'env' command to find variables\n");
      m->env = tmp;
      return (1);
    }
  else if (my_strcmp(m->word_tab[1], my_str_tab(m->env->var)[0]) == 0)
    remove_node(&m->env, &tmp);
  m->env = tmp;
  return (0);
}
