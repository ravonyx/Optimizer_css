NAME	=	optimizer_css
MANPATH = 	/usr/share/man/man1
BINPATH = 	/usr/bin/

SRCS	=	$(wildcard *.c)
OBJS	=	$(SRCS:.c=.o)

CC	=	gcc
CFLAGS	+=	-W -g3 -Wall -Werror

ESGI_D	= 	libesgi 
LDFLAGS +=	-L$(ESGI_D) -lesgi

all: $(NAME)

$(NAME): $(OBJS) 
	@(cd $(ESGI_D) && $(MAKE))
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) 

clean:
	@(cd $(ESGI_D) && $(MAKE) clean)
	rm -f $(OBJS)

distclean:	clean
	@(cd $(ESGI_D) && $(MAKE) distclean)
	rm -f $(NAME)

rebuild:	distclean all

install: 
	cp Man/$(NAME) $(MANPATH)/optimizer_css.1
	gzip $(MANPATH)/optimizer_css.1
	cp $(NAME) $(BINPATH)

