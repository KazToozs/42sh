/*
** my_put_in_list.c for push_swap in /home/pallua_j/rendu/Progelem/CPE_2014_Pushswap/function
**
** Made by jules palluau
** Login   <pallua_j@epitech.net>
**
** Started on  Tue Dec  2 14:17:15 2014 jules palluau
** Last update Sat May 16 14:41:32 2015 jules palluau
*/

#include "alias.h"

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
  if (list == NULL)
    return (elem);
  tmp = list;
  while (tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = elem;
  elem->prev = tmp;
  return (list);
}
