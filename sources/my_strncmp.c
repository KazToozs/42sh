/*
** my_strncmp.c for my_strncmp in /home/pallua_j/rendu/Piscine_C_J06/ex_06
** 
** Made by jules palluau
** Login   <pallua_j@epitech.net>
** 
** Started on  Mon Oct  6 15:46:10 2014 jules palluau
** Last update Mon Oct 20 20:27:34 2014 jules palluau
*/

int	my_strncmp(char *s1, char *s2, int n)
{
  int	x;

  x = 0;
  while (s1[x] != '\0' && s2[x] != '\0' && x < n)
    {
      if (s1[x] != s2[x])
	return (s1[x] - s2[x]);
      x++;
    }
  return (0);
}
