##
## EPITECH PROJECT, 2022
## Project Zappy
## File description:
## Makefile
##

SERVER		=	server/

CLI_AI			=	ai_cli/

CLI_GRAPH			=	graphical_cli/

EXEC_SERVER	=	zappy_server

EXEC_AI	=	zappy_ai

EXEC_GRAPH	=	zappy_gui

all:
				make -C $(SERVER)
				mv $(SERVER)$(EXEC_SERVER) .
				make -C $(CLI_AI)
				mv $(CLI_AI)$(EXEC_AI) .
				make -C $(CLI_GRAPH)
				mv $(CLI_GRAPH)$(EXEC_GRAPH) .

$(EXEC_SERVER):
				make -C $(SERVER)
				mv $(SERVER)$(EXEC_SERVER) .

$(EXEC_AI):
				make -C $(CLI_AI)
				mv $(CLI_AI)$(EXEC_AI) .

$(EXEC_GRAPH):
				make -C $(CLI_GRAPH)
				mv $(CLI_GRAPH)$(EXEC_GRAPH) .

debug:
				make -C $(SERVER) debug
				mv $(SERVER)$(EXEC_SERVER) .
				make -C $(CLI_AI) debug
				mv $(CLI_AI)$(EXEC_AI) .
				make -C $(CLI_GRAPH) debug
				mv $(CLI_GRAPH)$(EXEC_GRAPH) .

clean:
				make -C $(SERVER) clean
				make -C $(CLI_AI) clean
				make -C $(CLI_GRAPH) clean

fclean:			clean
				$(RM) $(EXEC_SERVER)
				$(RM) $(EXEC_AI)
				$(RM) $(EXEC_GRAPH)
				make -C $(SERVER) fclean
				make -C $(CLI_AI) fclean
				make -C $(CLI_GRAPH) fclean

tclean:			clean
				make -C $(SERVER) tclean
				make -C $(CLI_AI) tclean
				make -C $(CLI_GRAPH) tclean

re:				fclean all

rdebug:			fclean debug

tests_run:
				make -C $(SERVER) tests_run
				make -C $(CLI_AI) tests_run
				make -C $(CLI_GRAPH) tests_run

.PHONY:			all clean fclean re tests_run rdebug tclean $(EXEC_SERVER) $(EXEC_AI) $(EXEC_GRAPH)
