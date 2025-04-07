##
## EPITECH PROJECT, 2025
## B-OOP-400-STG-4-1-arcade-mathieu.barleon
## File description:
## Makefile
##

LIBS	=	NCurses 	\
			SDL 		\
			SFML		\

all:        $(LIBS)
debug:      $(LIBS)
clean:      $(LIBS)
fclean:     clean $(LIBS)
re:         fclean all

$(LIBS):
	@case "$(MAKECMDGOALS)" in \
		debug)	$(MAKE) -C $@ debug ;; \
		clean)	$(MAKE) -C $@ clean ;; \
		fclean)	$(MAKE) -C $@ fclean ;; \
		re)		$(MAKE) -C $@ re;; \
		*)		$(MAKE) -C $@ ;; \
	esac

.PHONY: all debug clean fclean re $(LIBS)
