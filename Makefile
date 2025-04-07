##
## EPITECH PROJECT, 2025
## B-OOP-400-STG-4-1-arcade-mathieu.barleon
## File description:
## Makefile
##

CXX				=	g++

CORE_SRC		=	src/Core/Core.cpp		\
					src/Main/main.cpp		\
					src/Utils/Error.cpp		\
					src/Utils/GetLib.cpp	\
					src/Utils/Logger.cpp	\

CORE_OBJ		=	$(CORE_SRC:.cpp=.o)

CORE_NAME		=	arcade

GAME_FOLDER		=	src/Games

GRAPH_FOLDER	=	src/Graphicals

CXXFLAGS		=	-W -Wall -Wextra -std=c++20 -iquote ./include/

DEBUG_FALGS		=	-g

debug:				CXXFLAGS += $(DEBUG_FALGS)
debug:				all

all:				core graphicals games

core_debug:			CXXFLAGS += $(DEBUG_FALGS)
core_debug:			core

core:				$(CORE_NAME)

games_debug:
					$(MAKE) -C $(GAME_FOLDER) debug

games:
					$(MAKE) -C $(GAME_FOLDER)

graphicals_debug:
					$(MAKE) -C $(GRAPH_FOLDER) debug

graphicals:
					$(MAKE) -C $(GRAPH_FOLDER)

$(CORE_NAME):		$(CORE_OBJ)
					$(CXX) -o $(CORE_NAME) $(CORE_OBJ)

clean:
					rm -f $(CORE_OBJ)
					$(MAKE) -C $(GAME_FOLDER) clean
					$(MAKE) -C $(GRAPH_FOLDER) clean


fclean:				clean
					rm -f $(CORE_NAME)
					$(MAKE) -C $(GAME_FOLDER) fclean
					$(MAKE) -C $(GRAPH_FOLDER) fclean

re:					fclean all

.PHONY:				debug					\
					all						\
					core_debug				\
					core					\
					games_debug				\
					games					\
					graphicals_debug		\
					clean					\
					fclean					\
					re						\
