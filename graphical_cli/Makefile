##
## EPITECH PROJECT, 2022
## Project Zappy
## File description:
## Makefile zappy_gui
##

CXX			=	g++

NAME		=	zappy_gui

NAME_TEST	=	unit_test

CXXFLAGS	=	-o $(NAME)			\
				-iquote ./include	\
				-iquote ../utils/client\
				-lpthread\

LDFLAGS		+=	--coverage -lcriterion

all:			$(NAME)

debug:			CXXFLAGS +=	-g
debug:			$(NAME)

$(NAME):
				cp gui_launch $(NAME)

clean:

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re debug
