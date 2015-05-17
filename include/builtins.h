/*
** builtins.h for minishell1 in /home/toozs-_c/Prog_tests/shell1/sources/include
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Tue Jan 20 20:05:19 2015 cristopher toozs-hobson
** Last update Sun May 17 12:48:40 2015 cristopher toozs-hobson
*/

#ifndef _BIN_H_
#define _BIN_H_

typedef struct	s_bins
{
  int		(*ptr)(t_main *m);
  char		*str;
}		t_bins;

t_bins		g_bin[] =
  {
    {&escape, "exit"},
    {&cd, "cd"},
    {&cd, "cd.."},
    {&cd, ".."},
    {&remove_env_var, "unsetenv"},
    {&my_setenv, "setenv"},
    {&display_env, "env"},
    {&my_echo, "echo"},
    {NULL, NULL}
  };

#endif /* _BIN_H_ */
