##
## EPITECH PROJECT, 2025
## B-OOP-400-STG-4-1-arcade-mathieu.barleon
## File description:
## Makefile
##

CXX				=	g++

CORE_SRC		=	src/Core/Core.cpp		\
					src/Main/main.cpp		\

CORE_OBJ		=	$(CORE_SRC:.cpp=.o)

CORE_NAME		=	arcade

GAME_FOLDER		=	src/Games

GRAPH_FOLDER	=	src/Graphicals

CXXFLAGS		=	-W -Wall -Wextra -std=c++20 -fPIC \
					-iquote ./include/

UNAME_S			:=	$(shell uname -s)

ifeq ($(UNAME_S),Linux)
	CXXFLAGS	+= -fno-gnu-unique
endif

UTILS			=	src/Utils

LDFLAGS			=	-L$(UTILS)

LDLIBS			=	-larcade_utils

DEBUG_FALGS		=	-g

debug:				CXXFLAGS += $(DEBUG_FALGS)
debug:				$(UTILS)
debug:				all

all:				$(UTILS)
all:				graphicals games core

core_debug:			CXXFLAGS += $(DEBUG_FALGS)
core_debug:			$(UTILS)
core_debug:			core

core:				$(UTILS)
core:				$(CORE_NAME)

games_debug:		$(UTILS)
games_debug:
					$(MAKE) -C $(GAME_FOLDER) debug

games:				$(UTILS)
games:
					$(MAKE) -C $(GAME_FOLDER)

graphicals_debug:	$(UTILS)
graphicals_debug:
					$(MAKE) -C $(GRAPH_FOLDER) debug

graphicals:			$(UTILS)
graphicals:
					$(MAKE) -C $(GRAPH_FOLDER)

$(CORE_NAME):		$(CORE_OBJ)
					$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

clean:				$(UTILS)
clean:
					$(RM) $(CORE_OBJ)
					$(MAKE) -C $(GAME_FOLDER) clean
					$(MAKE) -C $(GRAPH_FOLDER) clean

fclean:				$(UTILS)
fclean:				clean
					$(RM) $(CORE_NAME)
					$(MAKE) -C $(GAME_FOLDER) fclean
					$(MAKE) -C $(GRAPH_FOLDER) fclean

re:					$(UTILS)
re:					fclean all

$(UTILS):
	@case "$(MAKECMDGOALS)" in \
		debug)	$(MAKE) -C $@ debug ;; \
		core_debug)	$(MAKE) -C $@ debug ;; \
		games_debug)	$(MAKE) -C $@ debug ;; \
		graphicals_debug)	$(MAKE) -C $@ debug ;; \
		clean)	$(MAKE) -C $@ clean ;; \
		fclean)	$(MAKE) -C $@ fclean ;; \
		re)		$(MAKE) -C $@ re;; \
		*)		$(MAKE) -C $@ ;; \
	esac

doc:
					doc/generate.sh && doc/open.sh

doc_clean:
					$(RM) -r doc/html doc/latex

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
					doc						\
					doc_clean				\
					$(UTILS)				\
