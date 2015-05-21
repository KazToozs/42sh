##
## Makefile for  in /home/msa_m/Epitech/Systeme_Unix/test/python/projet_en_c
## 
## Made by msa_m
## Login   <msa_m@epitech.net>
## 
## Started on  Mon May 11 18:27:36 2015 msa_m
## Last update Wed May 20 07:45:24 2015 msa_m
##

NAME	=	script

SRC	=	src/test.c		\
		src/main.c		\
		src/get_next_line.c	\
		src/my_str_to_wordtab.c	\
		src/my_realloc.c	\
		src/my_strdup.c		\
		src/auxiliary.c		\
		src/my_strlen.c		\
		src/my_strcpy.c		\
		src/aff_function.c	\

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

CFLAGS	+=	-W -Wall -Wextra
CFLAGS	+=	-g3
CFLAGS	+=	-I./include

all	:	$(NAME)

$(NAME)	: 	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean	:
		rm -f $(OBJ)

fclean	:	clean
		rm -f $(NAME)

re	:	fclean all
