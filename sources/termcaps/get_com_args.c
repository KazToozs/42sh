/*
** get_com_args.c for termcaps in /home/fernan_s/Desktop/termcaps/src
** 
** Made by Quentin Fernandez
** Login   <fernan_s@epitech.net>
** 
** Started on  Sun May 10 20:42:48 2015 Quentin Fernandez
** Last update Mon May 18 15:38:29 2015 cristopher toozs-hobson
*/

#include "termcaps.h"

char		*arg_to_str(t_str *str)
{
  char		*ret;
  int		i;

  i = 1;
  ret = NULL;
  if (!str)
    return (NULL);
  while (str->prev)
    str = str->prev;
  if (!(ret = realloc(ret, i)))
    return (NULL);
  ret[0] = 0;
  while (str)
    {
      if (str->val)
	{
	  i += strlen(str->val);
	  if (!(ret = realloc(ret, i)))
	    return (NULL);
	  ret = strcat(ret, str->val);
	}
      str = str->next;
    }
  return (ret);
}

char		*get_cmd_str()
{
  t_arg		arg;
  long		keys;

  if (init_term())
    return (NULL);
  arg.size = strlen(glo.prompt);
  arg.pos = strlen(glo.prompt);
  arg.str = NULL;
  arg.str = add_elem_to_list(arg.str, NULL);
  keys = 0;
  read(0, &keys, sizeof(long) - 1);
  while (keys != ENTER_KEYS)
    {
      if (key_check(&arg, (char *)&keys))
	{
	  reset_term();
	  return (NULL);
	}
      keys = 0;
      read(0, &keys, sizeof(long) - 1);
    }
  go_to_end(&arg);
  printf("\n");
  if (reset_term())
    return (NULL);
  return (arg_to_str(arg.str));
}
