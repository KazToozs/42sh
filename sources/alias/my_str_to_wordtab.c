/*
** my_str_to_wordtab.c for my_str_to_wordtab in /home/toozs-_c/rendu/Piscine_C_J08/ex_04
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Mon Nov  3 10:09:14 2014 cristopher toozs-hobson
** Last update Mon May 11 11:12:10 2015 jules palluau
*/

#include "alias.h"

int		count_word(char *str)
{
  int		i;
  int		cpt;

  i = 0;
  cpt = 0;
  while (str[i] != '\0')
    {
      if (str[i] >= 33 && str[i] <= 126
	  && str[i] != '=' && str[i] != '"')
	{
	  cpt++;
	  while ((str[i] && str[i] >= 33 && str[i] <= 126)
		 && str[i] != '=' && str[i] != '"')
	    i++;
	}
      else
	i++;
    }
  return (cpt);
}

int		count_char(char *str, int *i)
{
  int		cpt;

  cpt = 0;
  while (str[*i] && (str[*i] >= 33 && str[*i] <= 126
		     && str[*i] != '=') && str[*i] != '"')
    {
      cpt++;
      *i = *i + 1;
    }
  return (cpt);
}

char		**my_str_to_wordtab(char *str)
{
  int		i;
  int		words;
  int		size;
  char		**tab;

  i = 0;
  size = 0;
  words = count_word(str);
  if ((tab = malloc(sizeof(char *) * (words + 1))) == NULL)
    return (NULL);
  while (str[i] && words > 0)
    {
      if (str[i] >= 33 && str[i] <= 126
	  && str[i] != '=' && str[i] != '"')
	{
	  if ((tab[size] = my_strdup(str + i)) == NULL)
	    return (NULL);
	  tab[size++] [count_char(str, &i)] = '\0';
	  words = words - 1;
	}
      else
	i++;
    }
  tab[size] = NULL;
  return (tab);
}
