##
## EPITECH PROJECT, 2025
## B-OOP-400-STG-4-1-arcade-mathieu.barleon
## File description:
## Makefile by Mathieu
##

CXX				=	g++

SRC				=	Menu.cpp		\
					../AGame.cpp		\
					../../Core/Core.cpp	\

OBJ				=	$(SRC:.cpp=.o)

TARGET_FOLDER	=	../../../lib/

NAME			=	$(TARGET_FOLDER)arcade_menu.so

CXXFLAGS		=	-W -Wall -Wextra -std=c++20 -fPIC \
					-iquote ../../../include/ -iquote ../

UNAME_S			:=	$(shell uname -s)

ifeq ($(UNAME_S),Linux)
	CXXFLAGS	+= -fno-gnu-unique
endif

UTILS			=	../../Utils

LDFLAGS			=	-shared -L$(UTILS)

LDLIBS			=	-larcade_utils

DEBUG_FALGS		=	-g

debug:				CXXFLAGS += $(DEBUG_FALGS)
debug:				$(UTILS)
debug:				all

all:				$(UTILS)
all:				$(NAME)

$(NAME):			$(OBJ)
					$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

clean:				$(UTILS)
clean:
					$(RM) $(OBJ)

fclean:				$(UTILS)
fclean:				clean
					$(RM) $(NAME)

re:					$(UTILS)
re:					fclean all

$(UTILS):
	@case "$(MAKECMDGOALS)" in \
		debug)	$(MAKE) -C $@ debug ;; \
		clean)	$(MAKE) -C $@ clean ;; \
		fclean)	$(MAKE) -C $@ fclean ;; \
		re)		$(MAKE) -C $@ re;; \
		*)		$(MAKE) -C $@ ;; \
	esac

.PHONY:				debug					\
					all						\
					clean					\
					fclean					\
					re						\
					$(UTILS)				\
