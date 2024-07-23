##
## EPITECH PROJECT, 2022
## Project myteams
## File description:
## Makefile zappy_server
##

CC			=	gcc

SRC_ACTIONS	=	src/actions/action_ai/broadcast_text.c			\
				src/actions/action_ai/connect_nbr.c				\
				src/actions/action_ai/eject.c					\
				src/actions/action_ai/fork.c					\
				src/actions/action_ai/forward.c					\
				src/actions/action_ai/incantation.c				\
				src/actions/action_ai/inventory.c				\
				src/actions/action_ai/left.c					\
				src/actions/action_ai/look.c					\
				src/actions/action_ai/right.c					\
				src/actions/action_ai/set_object.c				\
				src/actions/action_ai/take_object.c				\
				src/actions/action_graph/get_content_map.c		\
				src/actions/action_graph/get_name_teams.c		\
				src/actions/action_graph/get_player_position.c	\
				src/actions/action_graph/get_content_tile.c		\
				src/actions/action_graph/get_player_inventory.c	\
				src/actions/action_graph/get_time_unit.c		\
				src/actions/action_graph/get_map_size.c			\
				src/actions/action_graph/get_player_level.c		\
				src/actions/action_graph/modify_time_unit.c		\
				src/actions/action_graph/get_player_info.c		\
				src/event/player_connection.c					\
				src/event/ejecting.c							\
				src/event/broadcasting.c						\
				src/event/start_incantation.c					\
				src/event/end_incantation.c						\
				src/event/dropping_resources.c					\
				src/event/collecting_resources.c				\
				src/event/player_death.c						\
				src/event/laying_egg.c							\
				src/event/layed_egg.c							\
				src/event/egg_hatching.c						\
				src/event/connection_to_egg.c					\
				src/event/hatched_egg_death.c					\
				src/event/player_inventory.c					\
				src/event/player_level.c						\
				src/event/end_team.c							\
				src/event/map_changed.c							\
				src/event/tile_changed.c						\
				src/event/player_moved.c						\

SRC_SERVER	=	src/server/server.c								\
				src/server/params.c								\
				src/server/norm_params.c						\
				src/server/handle_client.c						\
				src/server/message.c							\
				src/server/make_actions.c						\
				src/server/deal_teams.c							\
				src/server/deal_player.c						\
				src/server/deal_graphical.c						\
				src/server/deal_command.c						\
				src/server/deal_end_incantation.c				\
				src/server/deal_start_incantation.c				\
				src/server/deal_egg.c							\
				src/game/map.c									\
				src/game/free_map.c								\
				src/game/deal_cell.c							\
				src/socket_utils.c								\
				src/utils.c										\
				src/sound.c										\
				src/view.c										\
				src/string_utils.c								\
				src/timer.c										\
				src/parse.c										\
				src/server/victory.c							\

SRC			=	main.c											\
				$(SRC_ACTIONS)									\
				$(SRC_SERVER)									\

T_SRC		=	../tests/unit_test_server.c						\
				../tests/unit_test_game.c						\
				../tests/unit_test_params.c						\
				../tests/unit_test_command_ia.c					\
				../tests/unit_test_parse_command.c				\
				$(SRC_SERVER)									\
				$(SRC_ACTIONS)									\

OBJ			=	$(SRC:.c=.o)

NAME		=	zappy_server

T_NAME		=	unit_test

CFLAGS		=	-iquote ./include								\
				-lm												\

LDFLAGS		+=	--coverage -lcriterion

all:			$(NAME)

debug:			CFLAGS	+=	-g
debug:			$(NAME)

$(NAME):		$(OBJ)
				$(CC) $(CFLAGS) -O2 -o $(NAME) $(OBJ)

clean:
				$(RM) $(OBJ)

fclean:			clean
				$(RM) $(NAME)
				$(RM) $(T_NAME)

tclean:
				$(RM) *.gcno
				$(RM) *.gcda


re:				fclean all

tests_run:		$(T_SRC)
				$(CC) $(CFLAGS) -o $(T_NAME) $(T_SRC) $(LDFLAGS)
				./$(T_NAME)
				gcovr
				$(RM) *.gcno
				$(RM) *.gcda

.PHONY:			all clean fclean re tests_run tclean
