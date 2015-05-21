/*
** my_put_in_list.c for push_swap in /home/pallua_j/rendu/Progelem/CPE_2014_Pushswap/function
**
** Made by jules palluau
** Login   <pallua_j@epitech.net>
**
** Started on  Tue Dec  2 14:17:15 2014 jules palluau
** Last update Thu May 21 16:18:57 2015 jules palluau
*/

#include "alias.h"

t_alias		*my_free(t_alias *list, char *s)
{
  t_alias	*tmp;

  tmp = list;
  while (tmp->next != NULL)
    {
      tmp = tmp->next;
      if (my_strcmp(s, tmp->prev->src) == 0)
	delete_node(&tmp->prev);
    }
  if (my_strcmp(s, tmp->src) == 0)
    delete_node(&tmp);
  while (tmp->prev != NULL)
    tmp = tmp->prev;
  return (tmp);
}

int		my_check(char *s, char *end)
{
  if (my_strcmp(s, end) == 0)
    {
      fprintf(stderr, "Alias loop!\n");
      return (1);
    }
  if (my_strcmp(s, "alias") == 0)
    {
      fprintf(stderr, "Too dangerous alias!\n");
      return (1);
    }
  return (0);
}

t_alias		*my_put_alias_list(t_alias *list, char *s, char *end)
{
  t_alias	*elem;
  t_alias	*tmp;

  if ((elem = malloc(sizeof(t_alias))) == NULL)
    return (NULL);
  elem->prev = NULL;
  elem->next = NULL;
  elem->src = strdup(s);
  elem->new = strdup(end);
  if (my_check(s, end) != 0)
    return (list);
  if (list == NULL)
    return (elem);
  list = my_free(list, s);
  tmp = list;
  while (tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = elem;
  elem->prev = tmp;
  return (list);
}
