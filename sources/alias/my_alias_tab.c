/*
** my_alias_tab.c for 42sh in /home/pallua_j/tmp/alias/src
** 
** Made by jules palluau
** Login   <pallua_j@epitech.net>
** 
** Started on  Sat May 16 11:35:26 2015 jules palluau
** Last update Wed May 20 13:26:30 2015 Quentin Fernandez
*/

#include "alias.h"

int		counts_word(char *str)
{
  int		i;
  int		cpt;

  i = 0;
  cpt = 0;
  while (str[i] != '\0')
    {
      if (str[i] && str[i] != '\t' && str[i] != ' ' && str[i] != '"')
        {
          cpt++;
          while ((str[i] && str[i] != '\t' && str[i] != ' ' && str[i] != '"'))
	    i++;
        }
      else
        i++;
    }
  return (cpt);
}

int		counts_char(char *str, int *i)
{
  int		cpt;

  cpt = 0;
  while (str[*i] && str[*i] != '\t' && str[*i] != ' ' && str[*i] != '"')
    {
      cpt++;
      *i = *i + 1;
    }
  return (cpt);
}

char		**my_alias_tab(char *str)
{
  int		i;
  int		words;
  int		size;
  char		**tab;

  i = 0;
  size = 0;
  words = counts_word(str);
  if ((tab = malloc(sizeof(char *) * (words + 1))) == NULL)
    return (NULL);
  while (str[i] && words > 0)
    {
      if ((str[i] && str[i] != '\t' && str[i] != ' ' && str[i] != '"'))
        {
          if ((tab[size] = my_strdup(str + i)) == NULL)
            return (NULL);
          tab[size++] [counts_char(str, &i)] = '\0';
          words = words - 1;
        }
      else
        i++;
    }
  tab[size] = NULL;
  return (tab);
}
