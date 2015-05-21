/*
** test.h for  in /home/msa_m/Epitech/Systeme_Unix/test/python
** 
** Made by msa_m
** Login   <msa_m@epitech.net>
** 
** Started on  Mon May 11 17:57:19 2015 msa_m
** Last update Tue May 19 13:59:06 2015 msa_m
*/

#ifndef TEST_H_
# define TEST_H_

/*
** Include
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

/*
** Prototype
*/

void	my_putchar(char n, int fd);
void	my_putstr(char *str, int fd);
void	my_putnbr(int nb, int fd);
void	free_tab(char **tab);
int	all_test(char *ex, char **env, char *test);
int	my_error(char *str);
int	my_strlen(char *str);
char	*my_strdup(char *src);
char	*my_strcpy(char *dest, char *src);
char	*get_next_line(const int fd);
char	**my_str_tab(char *str);

/*
** Structure
*/

typedef struct	s_data
{
  int		fd_file;
  int		pipefd[2];
  int		stdout_cpy;
  int		stdin_cpy;
}		t_data;

#endif /* !TEST_H_ */
