##
## EPITECH PROJECT, 2025
## B-OOP-400-STG-4-1-arcade-mathieu.barleon
## File description:
## Makefile
##

CXX				=	g++

AR				=	ar

SRC				=	Error.cpp				\
					GetLib.cpp				\
					Logger.cpp				\

OBJ				=	$(SRC:.cpp=.o)

NAME			=	libarcade_utils.a

CXXFLAGS		=	-W -Wall -Wextra -std=c++20 -fPIC \
					-iquote ../../include/ -iquote .

UNAME_S			:=	$(shell uname -s)

ifeq ($(UNAME_S),Linux)
	CXXFLAGS	+= -fno-gnu-unique
endif

DEBUG_FALGS		=	-g

ARFLAGS			=	-rc

debug:				CXXFLAGS += $(DEBUG_FALGS)
debug:				all

all:				$(NAME)

$(NAME):			$(OBJ)
					$(AR) $(ARFLAGS) $@ $^

clean:
					$(RM) $(OBJ)


fclean:				clean
					$(RM) $(NAME)

re:					fclean all

.PHONY:				debug					\
					all						\
					clean					\
					fclean					\
					re						\
