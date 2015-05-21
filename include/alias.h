/*
** alias.h for 42sh in /home/pallua_j/tmp/alias
** 
** Made by Jules Palluau
** Login   <pallua_j@epitech.net>
** 
** Started on  Mon May  4 15:26:38 2015 Jules Palluau
** Last update Thu May 21 10:41:34 2015 jules palluau
*/

#ifndef ALIAS_H_
# define ALIAS_H_

/*
************* Include *************
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "minishell.h"
#include "get_next_line.h"
#include "my.h"

/*
*************** Structure **************
*/

typedef struct		s_alias
{
  struct s_alias	*next;
  char			*src;
  char			*new;
  struct s_alias	*prev;
}			t_alias;

typedef struct		s_file
{
  int			fd;
  int			statement;
  char			*exp;
  t_alias		*alias;
}			t_file;

/*
************** Macros ****************
*/

# define ALIAS_FILE	".42sh"

/*
************** Prototypes alias ***************
*/

t_alias	*my_put_alias_list(t_alias *list, char *src, char *end);
void	delete_node(t_alias **list);
char	**my_str_to_wordtab(char *str);
char	**my_alias_tab(char *str);
int	tablen(char **tab);
char	*alias(char *s, t_file *file);
char	*new_line(char **tab, int x);

#endif /* !ALIAS_H_ */
