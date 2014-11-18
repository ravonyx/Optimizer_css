NAME	=	libesgi.a

SRCS	=	$(wildcard *.c)

OBJS	=	$(SRCS:.c=.o)

CFLAGS	+=	-W -Wall -Werror

CC	=	gcc
AR	=	ar
RANLIB	=	ranlib

all:	$(NAME)

$(NAME):	$(OBJS)
	$(AR) r $(NAME) $(OBJS)
	$(RANLIB) $(NAME)

clean:
	rm -f $(OBJS)

distclean:	clean
	rm -f $(NAME)

rebuild:	distclean all

.PHONY: all clean distclean rebuild
