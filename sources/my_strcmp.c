/*
** my_strcmp.c for my_strcmp in /home/toozs-_c/rendu/Piscine_C_J06/ex_05
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Wed Oct  8 15:04:55 2014 cristopher toozs-hobson
** Last update Wed Jan 21 11:26:49 2015 cristopher toozs-hobson
*/

#include <stdlib.h>

int	my_strcmp(char *s1, char *s2)
{
  int	i;

  i = 0;
  if (s1 != NULL && s2 != NULL)
    {
      while (s1[i])
	{
	  if (s1[i] < s2[i])
	    return (-1);
	  if (s1[i] > s2[i])
	    return (1);
	  i++;
	}
      if (s1[i] < s2[i])
	return (-1);
      if (s1[i] > s2[i])
	return (1);
      return (0);
    }
  else
    return (-2);
}
