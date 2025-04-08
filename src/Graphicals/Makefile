##
## EPITECH PROJECT, 2025
## B-OOP-400-STG-4-1-arcade-mathieu.barleon
## File description:
## Makefile
##

LIBS	=	NCurses 	\
			SDL 		\
			SFML		\

UTILS	=	../Utils

all:		$(UTILS)
all:        $(LIBS)

debug:		$(UTILS)
debug:      $(LIBS)

clean:		$(UTILS)
clean:      $(LIBS)

fclean:		clean
fclean:		$(UTILS)
fclean:     $(LIBS)

re:         fclean all

$(LIBS):
	@case "$(MAKECMDGOALS)" in \
		debug)	$(MAKE) -C $@ debug ;; \
		clean)	$(MAKE) -C $@ clean ;; \
		fclean)	$(MAKE) -C $@ fclean ;; \
		re)		$(MAKE) -C $@ re;; \
		*)		$(MAKE) -C $@ ;; \
	esac

$(UTILS):
	@case "$(MAKECMDGOALS)" in \
		debug)	$(MAKE) -C $@ debug ;; \
		clean)	$(MAKE) -C $@ clean ;; \
		fclean)	$(MAKE) -C $@ fclean ;; \
		re)		$(MAKE) -C $@ re;; \
		*)		$(MAKE) -C $@ ;; \
	esac

.PHONY: all debug clean fclean re $(LIBS) $(UTILS)
