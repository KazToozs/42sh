/*
** env_bins.c for minishell1 in /home/toozs-_c/Prog_tests/shell1/first_try
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sat Jan 31 00:30:58 2015 cristopher toozs-hobson
** Last update Wed Mar 25 10:02:41 2015 cristopher toozs-hobson
*/

#include "minishell.h"
#include "my.h"

void		add_env(char *var, char *value)
{
  char		*new;
  t_env		*tmp;

  tmp = glo.env;
  while (glo.env != NULL && (my_strcmp(var, my_str_tab(glo.env->var)[0]) != 0))
    glo.env = glo.env->next;
  if (glo.env != NULL)
    {
      new = my_strcat(my_str_tab(glo.env->var)[0], "=");
      new = my_strcat(new, value);
      glo.env->var = new;
    }
  else
    {
      glo.env = tmp;
      new = my_strcat(var, "=");
      new = my_strcat(new, value);
      my_put_in_list_end(&glo.env, new, &tmp);
    }
  glo.env = tmp;
}

int		my_setenv()
{
  if (glo.word_tab[1] != NULL)
    add_env(glo.word_tab[1], glo.word_tab[2]);
  else
    my_putstr_err("Missing argument. Use: setenv [-var] [-value]\n");
  return (0);
}

void		my_show_list(t_env *list)
{
  t_env		*tmp;

  tmp = list;
  while (tmp != NULL)
    {
      if (tmp->var != NULL)
        {
          my_putstr(tmp->var);
          my_putchar('\n');
        }
      tmp = tmp->next;
    }
}

int		display_env()
{
  if (glo.env != NULL)
    my_show_list(glo.env);
  else
    my_putstr_err("No environment variables to display\n");
  return (0);
}

int		remove_env_var()
{
  t_env		*tmp;

  tmp = glo.env;
  if (!glo.word_tab[1])
    {
      my_putstr_err("Missing argument. Use: unsetenv [-var]\n");
      return (1);
    }
  while (glo.env != NULL &&
         (my_strcmp(glo.word_tab[1], my_str_tab(glo.env->var)[0]) != 0))
    glo.env = glo.env->next;
  if (glo.env == NULL)
    my_putstr_err("Invalid variable: use 'env' command to find variables\n");
  else if (my_strcmp(glo.word_tab[1], my_str_tab(glo.env->var)[0]) == 0)
    remove_node(&glo.env, &tmp);
  glo.env = tmp;
  return (0);
}
