/*
** my_strcpy.c for my_strcpy in /home/toozs-_c/rendu/Piscine_C_J06/ex_01
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Mon Oct  6 10:33:09 2014 cristopher toozs-hobson
** Last update Tue Feb 24 13:53:31 2015 cristopher toozs-hobson
*/

char	*my_strcpy(char *dest, char *src)
{
  int	n;

  n = 0;
  while (src[n] != '\0')
    {
      dest[n] = src[n];
      n = n + 1;
    }
  return (dest);
}
