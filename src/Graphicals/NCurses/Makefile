##
## EPITECH PROJECT, 2025
## B-OOP-400-STG-4-1-arcade-mathieu.barleon
## File description:
## Makefile
##

CXX				=	g++

SRC				=	NCursesDisplayModule.cpp	\
					../ADisplayModule.cpp		\
					../../Utils/Error.cpp		\
					../../Utils/GetLib.cpp		\
					../../Utils/Logger.cpp		\

OBJ				=	$(SRC:.cpp=.o)

NAME			=	../../../lib/arcade_ncurses.so

CXXFLAGS		=	-W -Wall -Wextra -std=c++20 -fPIC \
					-iquote ../../../include/ -iquote ../

LDFLAGS			=	-shared

LDLIBS			=	-lncurses

DEBUG_FALGS		=	-g

debug:				CXXFLAGS += $(DEBUG_FALGS)
debug:				all

all:				$(NAME)

$(NAME):			$(OBJ)
					$(CXX) $(LDFLAGS) -o $(NAME) $(OBJ) $(LDLIBS)

clean:
					rm -f $(OBJ)


fclean:				clean
					rm -f $(NAME)

re:					fclean all

.PHONY:				debug					\
					all						\
					clean					\
					fclean					\
					re						\
