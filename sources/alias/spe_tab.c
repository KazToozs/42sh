/*
** spe_tab.c for 42sh in /home/pallua_j/tmp/alias/src
** 
** Made by jules palluau
** Login   <pallua_j@epitech.net>
** 
** Started on  Mon May 11 15:32:35 2015 jules palluau
** Last update Mon May 18 15:52:38 2015 pallua
*/

#include "alias.h"

int		tablen(char **tab)
{
  int		x;

  x = 0;
  while (tab[x] != NULL)
    x++;
  return (x);
}
