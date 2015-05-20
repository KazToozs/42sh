/*
** delete_node.c for 42SH in /home/pallua/dump/pallua_j/tmp/42test_jules/sources/alias
** 
** Made by pallua
** Login   <pallua@epitech.net>
** 
** Started on  Tue May 19 10:25:29 2015 pallua
** Last update Tue May 19 10:26:42 2015 pallua
*/

#include "alias.h"

void		delete_node(t_alias **list)
{
  t_alias	*tmp_next;
  t_alias	*tmp_prev;
  t_alias	*del;

  tmp_next = NULL;
  tmp_prev = NULL;
  if ((*list)->next)
    tmp_next = (*list)->next;
  if ((*list)->prev)
    tmp_prev = (*list)->prev;
  del = (*list);
  if (tmp_next)
    (*list) = tmp_next;
  else if (tmp_prev)
    (*list) = tmp_prev;
  else
    (*list) = NULL;
  if (tmp_prev)
    tmp_prev->next = tmp_next;
  if (tmp_next)
    tmp_next->prev = tmp_prev;
  free(del->src);
  free(del->new);
  free(del);
}
