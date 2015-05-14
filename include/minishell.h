/*
** minishell.h for minishell2 in /home/toozs-_c/Prog_tests/minishell2_tests/sources/include
** 
** Made by cristopher toozs-hobson
** Login   <toozs-_c@epitech.net>
** 
** Started on  Wed Feb  4 16:32:50 2015 cristopher toozs-hobson
** Last update Thu May 14 16:18:33 2015 cristopher toozs-hobson
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

typedef struct	s_stat
{
  char		*mess;
  int		sig;
}		t_stat;

typedef struct	s_left
{
  int		in_cpy;
  int		out_cpy;
  char		**tab;
  int		pipefd[2];
  char		**ret;
}		t_left;

typedef struct	s_pipe
{
  int		in_cpy;
  int		out_cpy;
  int		pipefd[2];
  int		check;
}		t_pipe;

typedef struct	s_main
{
  struct s_tree	*tree;
  int		ret;
  int		sig;
  char		**word_tab;
}		t_main;

typedef struct	s_exec
{
  int		(*ptr)(t_tree *root, t_main *m);
  char		op;
}		t_exec;

typedef struct	s_glo
{
  struct s_env	*env;
  pid_t		pid;
  pid_t		gpid;
  int		fg;
  int		x;
}		g_glo;

extern g_glo	glo;

void		display_prompt(int fd, t_env *env);
int		my_shell(char *ret, t_main *m);
int		make_tree(t_tree **root, char *ret);
void		manage_error(char *str);
void		status_error(int status);
int		status_check(int status, t_main *m);
int		manage_signal();
int		make_env(char **env);
int		execute_function(char *ret, t_main *m);
int		execute_fork(char **word_tab, t_env *env, t_main *m);
char		*find_var(t_env *env, char *var);
char		*env_var_val(t_env *env, char *var, int display);
int		my_put_in_list_end(t_env **list, char *data, t_env **mark);
void		remove_node(t_env **node, t_env **mark);
void		free_tab(char **tab);
int		launch_tree(t_tree *root, t_main *m);
char		**my_realloc_tab(char **str, int size);
void		free_tree(t_tree *root);
int		perform_check(char *ret, int *i, int *check, t_tree **root);
int		check_op(char *ret);
int		quotes(char c, int tru);
char		*check_access(char **tab, char *function);

/*
** Built-ins
*/

int		cd(t_main *m);
int		cd_tilde(t_main *m);
int		cd_minus(t_main *m);
int		cd_ddot(t_main *m);
int		cd_home(t_main *m);
char		*remove_end_chars(char c, char *str, int start);
int		escape(t_main *m);
void		add_env(char *var, char *value);
int		remove_env_var(t_main *m);
int		my_setenv(t_main *m);
void		my_show_list(t_env *list);
int		display_env();
int		my_echo(t_main *m);

/*
** Operations
*/

int		pipe_op(t_tree *root, t_main *m);
int		or_op(t_tree *root, t_main *m);
int		and_op(t_tree *root, t_main *m);
int		semi_colon(t_tree *root, t_main *m);
int		right_op_check(t_tree *root, t_main *m);
int		right_op(t_tree *root, int type, t_main *m);
int		dbl_left_close(t_left *l, t_tree *root, t_main *m);
void		dbl_left_cmp(t_left *l);
int		dbl_left_read(t_left *l);
int		double_left_fork(t_tree *root, t_main *m);
int		left_op(t_tree *root, t_main *m);
int             or_check(char *ret, int *n);
int             redir_check(char *ret, int *n);
int		and_check(char *ret, int *n);
void		redir_set(int *check, t_tree **root, int *i, char *ret);
void		set_file_word(t_tree *root, char ***tab);

#endif
