##
## EPITECH PROJECT, 2025
## B-OOP-400-STG-4-1-arcade-mathieu.barleon
## File description:
## Makefile
##

CXX				=	g++

SRC				=	SFMLDisplayModule.cpp		\
					../ADisplayModule.cpp		\
					../../Utils/Error.cpp		\
					../../Utils/GetLib.cpp		\
					../../Utils/Logger.cpp		\

OBJ				=	$(SRC:.cpp=.o)

TARGET_FOLDER	=	../../../lib/

NAME			=	$(TARGET_FOLDER)arcade_sfml.so

CXXFLAGS		=	-W -Wall -Wextra -std=c++20 -fPIC \
					-iquote ../../../include/ -iquote ../

LDFLAGS			=	-shared

LDLIBS			=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

DEBUG_FALGS		=	-g

debug:				CXXFLAGS += $(DEBUG_FALGS)
debug:				all

all:				$(NAME)

$(NAME):			$(OBJ)
					$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)
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
