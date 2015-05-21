/*
** termcaps.h for termcaps in /home/fernan_s/Desktop/termcaps/include
** 
** Made by Quentin Fernandez
** Login   <fernan_s@epitech.net>
** 
** Started on  Sat May  9 23:22:10 2015 Quentin Fernandez
** Last update Wed May 20 21:00:10 2015 Quentin Fernandez
*/

#ifndef _TERMCAPS_H_
# define _TERMCAPS_H_

/*
** Define function KEYS
*/

# define ENTER_KEYS		10
# define CTRL_D			4
# define UP_KEYS		4283163
# define DOWN_KEYS		4348699
# define LEFT_KEYS		4479771
# define RIGHT_KEYS		4414235
# define ESC_KEYS		27
# define CTRL_LEFT_KEYS		74995417045787
# define CTRL_RIGHT_KEYS	73895905418011
# define CTRL_UP_KEYS		71696882162459
# define CTRL_DOWN_KEYS		72796393790235
# define BACK_KEYS		127
# define DEL_KEYS		2117294875
# define CTRL_A_KEYS		1
# define CTRL_E_KEYS		5
# define CTRL_L_KEYS		12
# define END_KEYS		4607771
# define HOME_KEYS		4738843

/*
** include System
*/

#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <term.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
** Struct
*/

typedef struct s_str	t_str;
typedef struct s_arg	t_arg;
typedef struct s_key	t_key;
typedef struct s_env	t_env;
typedef	int	(*t_func_k)(t_arg *);

struct		s_str
{
  char		*val;
  t_str		*next;
  t_str		*prev;
};

struct		s_arg
{
  int		size;
  int		pos;
  t_str		*str;
};

struct		s_key
{
  long		key;
  t_func_k	func;
};

typedef struct  s_glo
{
  struct s_env  *env;
  t_arg		arg;
  pid_t         pid;
  pid_t         gpid;
  int           x;
  char          *prompt;
}               g_glo;

extern g_glo	glo;

/*
** Prototypes
*/

int		manage_signal();
char		*env_var_val(t_env *, char *, int);
void		display_prompt(int fd, t_env *env);

/*
** print_val.c
*/

int		put_c(int c);
int		put_str(char *str);
void		print_list(t_arg *, t_str *);
void		print_list_del(t_arg *, t_str *);

/*
** list_str.c
*/

t_str		*add_elem_to_list(t_str *, char *);
t_str		*rm_prev_elem(t_str *);
t_str		*rm_to_next_elem(t_str *);
t_str		*free_all_list(t_str *);

/*
** termcaps.c
*/

void		check_term();
int		init_term();
int		reset_term();

/*
** pos_func.c
*/

void		save_pos();
void		load_pos();
int		home_of_str(t_arg *);
int		go_to_end(t_arg *);

/*
** ctrl_func.c
*/

int		clear_l_screen(t_arg *arg);
int		left_word(t_arg *);
int		right_word(t_arg *);

/*
** del_func.c
*/

int		ctrl_d_key(t_arg *);
int		del_key_func(t_arg *);

/*
** left_keys.c
*/

int	del_left(t_arg *);
int	go_left(t_arg *);
void	get_back(t_arg *);
void	get_up(int);

/*
** right_key.c
*/

void	get_down(int);
int	go_right(t_arg *);


/*
** keys_check.c
*/

int		is_cmd_key(unsigned char *);
int		key_check(t_arg *, char *);


/*
** get_com_args.c
*/

char		*get_cmd_str();
char		*arg_to_str(t_str *str);
int		init_arg();

#endif /*_TERMCAPS_H_*/
