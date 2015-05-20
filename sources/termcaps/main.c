/*
** main.c for termcaps in /home/fernan_s/Desktop/termcaps/src
** 
** Made by Quentin Fernandez
** Login   <fernan_s@epitech.net>
** 
** Started on  Sat May  9 23:20:41 2015 Quentin Fernandez
** Last update Wed May 20 17:11:11 2015 cristopher toozs-hobson
*/

#include "termcaps.h"

int		main()
{
  char		*str;

  if (init_term() == -1)
    {
      printf("Nique ta mère\n");
      return (0);
    }
  while ((str = get_cmd_str()))
    {
      printf("Commande Reçu\n\t[%s]\n", str);
      free(str);
      str = NULL;
    }
  if (reset_term() == -1)
    {
      printf("HéHé t'es dans la merde\n");
      return (0);
    }
  printf("it's Ok\n");
  return (0);
}
