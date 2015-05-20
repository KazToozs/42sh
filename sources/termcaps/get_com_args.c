/*
** get_com_args.c for termcaps in /home/fernan_s/Desktop/termcaps/src
** 
** Made by Quentin Fernandez
** Login   <fernan_s@epitech.net>
** 
** Started on  Sun May 10 20:42:48 2015 Quentin Fernandez
** Last update Wed May 20 13:02:56 2015 cristopher toozs-hobson
*/

#include "termcaps.h"
#include "get_next_line.h"

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

int		check_enter(long c)
{
  int		i;

  i = 0;
  while (i < 64)
    {
      if (c << i % 255 == ENTER_KEYS)
	return (0);
      i += 8;
    }
 return (1);
}

t_str		*free_all_list(t_str *str)
{
  while (str->next)
      str = rm_to_next_elem(str);
  free(str->val);
  free(str);
  return (NULL);
}

int		init_arg()
{
  if (glo.arg.str)
    glo.arg.str = free_all_list(glo.arg.str);
  if (glo.prompt)
    {
      glo.arg.size = strlen(glo.prompt);
      glo.arg.pos = strlen(glo.prompt);
    }
  else
    {
      glo.arg.pos = 0;
      glo.arg.size = 0;
    }
  if (!(glo.arg.str = add_elem_to_list(glo.arg.str, NULL)))
    return (-1);
  return (0);
}

long		get_keys()
{
  long		key;

  key = 0;
  read(0, &key, sizeof(long) - 1);
  return (key);
}

char		*get_cmd_str()
{
  long		keys;

  if (init_term())
    return (get_next_line(0));
  if (manage_signal())
    return (NULL);
  if (init_arg())
    return (NULL);
  while (check_enter((keys = get_keys())))
    {
      if (key_check(&glo.arg, (char *)&keys))
	{
	  reset_term();
	  return (NULL);
	}
    }
  go_to_end(&glo.arg);
  fprintf(stderr, "\n");
  if (reset_term())
    return (NULL);
  return (arg_to_str(glo.arg.str));
}
