/*
** builtins.h for minishell1 in /home/toozs-_c/Prog_tests/shell1/sources/include
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Tue Jan 20 20:05:19 2015 cristopher toozs-hobson
** Last update Tue Mar  3 11:01:11 2015 cristopher toozs-hobson
*/

#ifndef BIN_H_
#define BIN_H_

typedef struct	s_bins
{
  int		(*ptr)();
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

#endif
