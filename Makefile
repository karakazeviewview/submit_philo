
NAME			=	philo

SRCS			=	$(shell find src/ -name "*.c")

OBJS			=	$(SRCS:.c=.o)

INCLUDE			=	-I include

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror
DEBUG_FLAGS_MAC =	-g -fsanitize=address -fsanitize=undefined -pthread
GCC_FLAGS		=
THREAD_FLAGS	=	-g -fsanitize=undefined -fsanitize=thread -pthread
# THREAD_FLAGS	=	-g -fsanitize=thread -pthread

.c.o:
				$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
				
$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

PHONY			=	all
all:			$(NAME)

PHONY			+=	clean
clean:			
				$(RM) $(NAME)

PHONY			+=	fclean
fclean:			clean
				$(RM) $(NAME)
			
PHONY			+=	re
re:				fclean all

PHONY			+=	debug
debug:			CFLAGS +=	$(DEBUG_FLAGS)
debug:			re

PHONY			+=	debug_mac
debug_mac:		CFLAGS +=	$(DEBUG_FLAGS_MAC)
debug_mac:		re

PHONY			+=	thread
thread:			CFLAGS +=	$(THREAD_FLAGS)
thread:			re

PHONY			+=	gcc
gcc:			CFLAGS =	$(GCC_FLAGS)
gcc:			re

PHONY			+=	do
do:				all
				while [ 1 ]; do ./$(NAME) 200 1000 100 100 | tee -a output.txt && sleep 1;done


.PHONY:			$(PHONY)