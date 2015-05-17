/*
** get_next_line2.c for get_next_line in /home/toozs-_c/ProgElem_test/get_next_line_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Wed Nov 19 11:00:34 2014 cristopher toozs-hobson
** Last update Sun May 17 12:26:23 2015 cristopher toozs-hobson
*/

#include <stdlib.h>
#include "get_next_line.h"

void		buffer_clean(char *buffer, int size, char c)
{
  int		i;

  i = 0;
  while (i < size)
    buffer[i++] = c;
}

char		get_char(int fd)
{
  static char	buffer[BUFF_SIZE + 1] = {0};
  static int	i = 0;

  if (buffer[i] == '\0')
    {
      i = 0;
      buffer_clean(buffer, BUFF_SIZE + 1, 0);
      if (read(fd, buffer, BUFF_SIZE) <= 0)
	return (-1);
    }
  return (buffer[i++]);
}

char		*my_dup_free(char *buffer)
{
  char		*tmp;
  int		i;
  int		size;

  i = 0;
  size = 0;
  while (buffer[size] != '\0')
    size++;
  if ((tmp = malloc(sizeof(char) * (size + 1))) == NULL)
    return (NULL);
  while (buffer[i] != '\0')
    {
      tmp[i] = buffer[i];
      i++;
    }
  tmp[i] = '\0';
  free(buffer);
  return (tmp);
}

char		*get_next_line(const int fd)
{
  char		*buffer;
  int		i;
  int		j;
  char		c;

  if ((buffer = malloc(sizeof(char) * (BUFF_SIZE + 1))) == NULL)
    return (NULL);
  i = 0;
  j = 1;
  buffer_clean(buffer, BUFF_SIZE + 1, 0);
  while ((c = get_char(fd)) != -1 && c != '\0' && c != '\n')
    {
      if (i >= (j * BUFF_SIZE))
	if ((buffer = my_realloc(buffer, sizeof(char)
				 * ((++j * BUFF_SIZE) + 1))) == NULL)
	  return (NULL);
      buffer[i++] = c;
    }
  if (c == -1 && buffer[0] == '\0')
    {
      free(buffer);
      return (NULL);
    }
  return (my_dup_free(buffer));
}
