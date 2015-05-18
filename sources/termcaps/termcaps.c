/*
** termcaps.c for termcaps in /home/fernan_s/Desktop/termcaps/src
** 
** Made by Quentin Fernandez
** Login   <fernan_s@epitech.net>
** 
** Started on  Sun May 10 17:52:29 2015 Quentin Fernandez
** Last update Sun May 10 18:20:18 2015 Quentin Fernandez
*/

#include "termcaps.h"

int			init_term()
{
  char			*n_term;
  struct termios	term;
  
  if (!(n_term = getenv("TERM")))
    return (-1);
  if (tgetent(NULL, n_term) == -1)
    return (-1);
  if (tcgetattr(0, &term) == -1)
    return (-1);
  term.c_lflag &= ~(ICANON);
  term.c_lflag &= ~(ECHO);
  term.c_cc[VMIN] = 1;
  term.c_cc[VTIME] = 0;
  if (tcsetattr(0, TCSADRAIN, &term) == -1)
    return (-1);
  return (0);
}

int			reset_term()
{
  struct termios	term;

  if (tcgetattr(0, &term) == -1)
    return (-1);
  term.c_lflag = (ICANON | ECHO);
  if (tcsetattr(0, 0, &term) == -1)
    return (-1);
  return (0);
}
