##
## EPITECH PROJECT, 2022
## Project Zappy
## File description:
## Makefile zappy_ai
##

CXX			=	g++

SRC_POJECT	=	src/AI/Params.cpp			\
				src/AI/Communication.cpp	\
				src/AI/Parser.cpp			\
				src/AI/CommandThread.cpp	\
				src/client/Client.cpp		\
				src/client/ErrorClient.cpp	\
				src/AI/Waiter.cpp			\
				src/AI/AiFunction.cpp		\
				src/AI/Enigma.cpp		\

SRC			=	main.cpp					\
				$(SRC_POJECT)				\

SRC_TEST	=	tests/unit_test_ai.cpp		\
				tests/unit_test_look.cpp	\
				tests/unit_test_params.cpp	\
				tests/unit_test_parser.cpp	\
				$(SRC_POJECT)				\

OBJ			=	$(SRC:.cpp=.o)

NAME		=	zappy_ai

NAME_TEST	=	unit_test

CXXFLAGS	=	-o $(NAME)			\
				-iquote ./src/AI	\
				-iquote ./src/client	\
				-lpthread\

LDFLAGS		+=	--coverage -lcriterion

all:			$(NAME)

debug:			CXXFLAGS +=	-g
debug:			$(NAME)

$(NAME):		$(OBJ)
				$(CXX) $(CXXFLAGS) $(OBJ)

clean:
				$(RM) $(OBJ)

fclean:			clean
				$(RM) $(NAME)
				$(RM) $(NAME_TEST)

re:				fclean all

tclean:
				$(RM) $(NAME_TEST)
				$(RM) *.gcno
				$(RM) *.gcda

tests_run:		$(SRC_TEST)
				$(CXX) $(CXXFLAGS) -o $(NAME_TEST) $(SRC_TEST) $(LDFLAGS)
				./$(NAME_TEST)
				gcovr
				$(RM) *.gcno
				$(RM) *.gcda

.PHONY:			all clean fclean re debug tests_run tclean
