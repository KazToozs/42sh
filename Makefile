##
## Makefile for makefile_test_minilibx in /home/toozs-_c/iGraph_test/tests
## 
## Made by cristopher toozs-hobson
## Login   <toozs-_c@epitech.net>
## 
## Started on  Wed Oct 29 15:09:44 2014 cristopher toozs-hobson
## Last update Thu May 14 16:19:59 2015 cristopher toozs-hobson
##

SRC	=	./sources/my_putchar.c		\
		./sources/my_putstr.c		\
		./sources/my_put_nbr.c		\
		./sources/my_strlen.c		\
		./sources/my_str_to_wordtab.c	\
		./sources/my_strcmp.c		\
		./sources/my_putstr_err.c	\
		./sources/my_strcpy.c		\
		./sources/my_strncpy.c		\
		./sources/my_strdup.c		\
		./sources/my_strcat.c		\
		./sources/my_realloc.c		\
		./sources/get_next_line.c	\
		./sources/tree.c		\
		./sources/tree_checks.c		\
		./sources/special_checks.c	\
		./sources/env.c			\
		./sources/env_bins.c		\
		./sources/echo_bins.c		\
		./sources/cd_bins.c		\
		./sources/built_ins.c		\
		./sources/fork_manage.c		\
		./sources/status.c		\
		./sources/access.c		\
		./sources/exec.c		\
		./sources/activate_tree.c	\
		./sources/pipe.c		\
		./sources/separator_ops.c	\
		./sources/right_op.c		\
		./sources/left_op.c		\
		./sources/ops_dbl_left.c	\
		./sources/signals.c		\
		./sources/auxiliary.c		\
		./sources/my_getnbr.c		\
		./sources/my_strncmp.c		\
		./sources/shell.c		\
		./sources/double_left.c		\
		./sources/main.c

NAME	=	42sh

CC	=	gcc

COMP	=	$(SRC:.c=.o)

CFLAGS	=	-W -Wall -Wextra

CFLAGS	+=	-I./include


all: $(NAME)

$(NAME): $(COMP)
	$(CC) -o $(NAME) $(SRC) $(CFLAGS)

clean: 
	rm -f $(COMP)

fclean: clean
	rm -f $(NAME)

re: fclean all
