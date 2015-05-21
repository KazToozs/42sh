/*
** new_str.c for 42sh in /home/pallua_j/tmp/alias/src
** 
** Made by jules palluau
** Login   <pallua_j@epitech.net>
** 
** Started on  Sun May 10 12:20:19 2015 jules palluau
** Last update Thu May 21 10:41:43 2015 jules palluau
*/

#include "alias.h"

void	reset(int *norm, int *simple, int *doub)
{
  (*norm) = 0;
  (*simple) = 0;
  (*doub) = 0;
}

int	condition(char *str, int *doub, int *simple)
{
  int	x;

  x = -1;
  while (str[++x])
    {
      if (str[x] == 39)
	{
	  if (++(*simple) > 1)
	    return (1);
	}
      else if (str[x] == '"')
	{
	  if (++(*doub) > 1)
	    return (1);
	}
    }
  return (0);
}

int		check_quote(char *str, char *tab)
{
  static int	simple = 0;
  static int	doub = 0;
  static int	norm = 0;

  if (str == NULL)
    {
      if (++norm > 1)
	{
	  reset(&norm, &simple, &doub);
	  return (1);
	}
      else
	return (0);
    }
  if (tab == NULL)
    {
      reset(&norm, &simple, &doub);
      return (1);
    }
  if (condition(str, &doub, &simple) != 0)
    {
      reset(&norm, &simple, &doub);
      return (1);
    }
  return (0);
}

char	*new_strr(char *first, char **second, int x)
{
  char	*new;
  int	i;
  int	n;

  i = 0;
  n = 0;
  if ((new = malloc(sizeof(char) *
		    (my_strlen(first) + my_strlen(second[x]) + 2))) == NULL)
    return (NULL);
  while (first != NULL && first[i] != '\0')
    {
      if (first[n] != 39 && first[n] != '"')
	new[i++] = first[n];
      n++;
    }
  n = -1;
  while (second[x] != NULL && second[x][++n] != '\0')
    {
      if (second[x][n] != 39 && second[x][n] != '"')
	new[i++] = second[x][n];
    }
  if (second[x + 1] != NULL)
    new[i++] = ' ';
  new[i] = '\0';
  return (new);
}

char	*new_line(char **tab, int x)
{
  char	*new;
  char	*line;

  new = NULL;
  while (check_quote(new, tab[x]) != 1)
    {
      if ((line = new_strr(new, tab, x)) == NULL)
	return (NULL);
      free(new);
      new = line;
      x++;
    }
  return (new);
}
