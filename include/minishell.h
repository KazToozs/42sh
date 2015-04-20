/*
** minishell.h for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests/sources/include
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Wed Feb  4 16:32:50 2015 cristopher toozs-hobson
** Last update Wed Mar 25 19:22:43 2015 cristopher toozs-hobson
*/

#ifndef SHELL_H_
#define SHELL_H_

#define WRITE_END 1
#define READ_END 0

#include <unistd.h>

typedef struct	s_env
{
  char		*var;
  struct s_env	*prev;
  struct s_env	*next;
}		t_env;

typedef struct	s_tree
{
  char		op;
  char		*exp;
  struct s_tree	*left;
  struct s_tree	*right;
}		t_tree;

typedef struct	s_left
{
  int		in_cpy;
  int		out_cpy;
  char		**tab;
  int		pipefd[2];
  char		**ret;
}		t_left;

typedef struct	s_glo
{
  struct s_env	*env;
  struct s_tree	*tree;
  pid_t		pid;
  int		x;
  char		**word_tab;
}		g_glo;

extern g_glo	glo;

void		make_tree(t_tree **root, char *ret);
void		manage_error(char *str);
void		manage_signal();
void		make_env(char **env);
void		execute_function(char *ret);
void		execute_fork(char **word_tab, t_env *env);
char		*find_var(t_env *env, char *var);
void		my_put_in_list_end(t_env **list, char *data, t_env **mark);
void		remove_node(t_env **node, t_env **mark);
void		free_tab(char **tab);
void		launch_tree(t_tree *root);
char		**my_realloc_tab(char **str, int size);
void		free_tree(t_tree *root);
void		perform_check(char *ret, int *i, int *check, t_tree **root);
int		check_op(char *ret);
int		quotes(char c, int tru);

/*
** Built-ins
*/

int		cd();
int		cd_tilde();
int		cd_minus();
int		cd_ddot();
int		cd_home();
char		*remove_slash(char c);
int		escape();
void            add_env(char *var, char *value);
int		remove_env_var();
int		my_setenv();
int		display_env();
int		my_echo();

/*
** Operations
*/

void		pipe_op(t_tree *root);
void		semi_colon(t_tree *root);
void		right_op(t_tree *root);
void		double_right(t_tree *root);
void		double_left_fork(t_tree *root);
void		left_op(t_tree *root);

#endif
