/*
** list_str.c for termcaps in /home/fernan_s/Desktop/termcaps/src
** 
** Made by Quentin Fernandez
** Login   <fernan_s@epitech.net>
** 
** Started on  Sun May 10 10:24:21 2015 Quentin Fernandez
** Last update Thu May 21 10:24:45 2015 cristopher toozs-hobson
*/

#include "termcaps.h"

t_str		*add_elem_to_list(t_str *str, char *val)
{
  t_str		*new;

  if (!(new = malloc(sizeof(t_str))))
    return (str);
  if (val)
    {
      if (!(new->val = strdup(val)))
	return (str);
    }
  else
    new->val = NULL;
  if (str)
    {
      new->prev = str;
      if (str->next)
	str->next->prev = new;
      new->next = str->next;
      str->next = new;
    }
  else
    {
      new->prev = NULL;
      new->next = NULL;
    }
  return (new);
}

t_str		*rm_prev_elem(t_str *str)
{
  t_str		*tmp;

  if (str->prev)
    {
      tmp = str->prev;
      tmp->next = str->next;
      if (str->next)
	str->next->prev = tmp;
      free(str->val);
      free(str);
      return (tmp);
    }
  else
    return (str);
}

t_str		*rm_to_next_elem(t_str *str)
{
  t_str		*tmp;

  if (str->next)
    {
      tmp = str->next;
      tmp->prev = str->prev;
      if (str->prev)
	str->prev->next = tmp;
      free(str->val);
      free(str);
      return (tmp);
    }
  else
    return (NULL);
}

t_str		*free_all_list(t_str *str)
{
  while (str->next)
    str = rm_to_next_elem(str);
  free(str->val);
  free(str);
  return (NULL);
}
