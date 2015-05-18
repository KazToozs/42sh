/*
** print_val.c for  in /home/fernan_s/Desktop/termcaps/src
** 
** Made by Quentin Fernandez
** Login   <fernan_s@epitech.net>
** 
** Started on  Sun May 17 04:19:35 2015 Quentin Fernandez
** Last update Sun May 17 04:43:42 2015 Quentin Fernandez
*/

#include "termcaps.h"

int		put_c(int c)
{
  return (write(1, &c, sizeof(int)));
}

int		put_str(char *str)
{
  return (write(1, str, strlen(str)));
}

void            print_list(t_arg *arg, t_str *str)
{
  (void)arg;
  if (str->val)
    put_str(str->val);
  save_pos();
  while (str->next)
    {
      str = str->next;
      if (str->val)
	put_str(str->val);
    }
  load_pos();
}

void            print_list_del(t_arg *arg, t_str *str)
{
  (void)arg;
  while (str->next)
    {
      if (str->val)
	put_str(str->val);
      str = str->next;
    }
  if (str->val)
    put_str(str->val);
}
