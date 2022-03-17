NAME=libmemory.a
TESTNAME=unit_test
SRCSDIR=srcs
OBJSDIR=objs
SRCS=ft_bzero.c  ft_memcpy.c  t_alloc.c  t_node.c  libmemory.c
SCRS_TEST=$(addprefix .unit_testing/, main.c)
OBJS=$(SRCS:%.c=$(OBJSDIR)/%.o)
CC = gcc
FLAGS = -Wall -Wextra -Werror -g
HDRS= includes

all: $(TESTNAME) $(NAME)

$(NAME): ${OBJS}
	@echo "// BUILDING $(NAME) //"
	@ar rc $(NAME) $(OBJS)
	@echo "Todo bien !"

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c $(HDRS)/$(NAME:.a=.h) Makefile
	@mkdir -p $(dir $@)
	@${CC} ${FLAGS} -c -I$(HDRS) -o $@ $<

$(TESTNAME): $(OBJS) $(SCRS_TEST)
	@echo "// UNIT_TESTING LOADING //"
	@$(CC) $(FLAGS) -I$(HDRS) $(SCRS_TEST) $(OBJS) -o $@
	@valgrind -q --show-leak-kinds=all --leak-check=yes ./$(TESTNAME) > /dev/null
	@echo "SUCCESS"

clean:
	rm -rf ${OBJSDIR}

fclean: clean
	${RM} ${NAME} $(TESTNAME)

re: fclean all

.PHONY: all clean fclean re
