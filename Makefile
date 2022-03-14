NAME=libmemory.a
SRCSDIR=srcs
OBJSDIR=objs
SRCS=ft_bzero.c  ft_memcpy.c  t_alloc.c  t_node.c  libmemory.c
OBJS=$(SRCS:%.c=$(OBJSDIR)/%.o)
CC = gcc
FLAGS = -Wall -Wextra -Werror -g
HDRS= includes

all: $(NAME)

$(NAME): ${OBJS}
	ar rc $(NAME) $(OBJS)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c $(HDRS)/$(NAME:.a=.h) Makefile
	@mkdir -p $(dir $@)
	${CC} ${FLAGS} -c -I$(HDRS) -o $@ $<

clean:
	rm -rf ${OBJSDIR}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
