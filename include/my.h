/*
** my.h for my_h in /home/toozs-_c/rendu/Piscine_C_J09/include
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Fri Oct 10 14:21:53 2014 cristopher toozs-hobson
** Last update Wed Mar 25 14:17:41 2015 cristopher toozs-hobson
*/

#ifndef LIB_MY_
# define LIB_MY_

char		**my_str_tab(char *str);
void		my_putchar(char c);
void		my_putstr(char *str);
char		*get_next_line(int fd);
int		my_strlen(char *str);
char		*my_strdup(char *str);
int		my_strcmp(char *s1, char *s2);
char		*my_strcat(char *first, char *second);
void		my_putstr_err(char *str);
char		*my_strcpy(char *dest, char *src);
char		*my_strncpy(char *dest, char *src, int n);

#endif
