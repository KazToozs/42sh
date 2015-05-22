/*
** get_next_line.h for get_next_line in /home/toozs-_c/rendu/get_next_line_tests
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Sun Nov 16 15:17:52 2014 cristopher toozs-hobson
** Last update Fri May 22 19:26:16 2015 cristopher toozs-hobson
*/

#ifndef G_N_L_H_
#define G_N_L_H_

#include <unistd.h>

#define BUFF_SIZE 4096

char	*get_next_line(const int fd);
char	*my_realloc(char *str, int size);

#endif /* G_N_L_H_ */
