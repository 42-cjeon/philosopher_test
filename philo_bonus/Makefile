CC = clang
CFLAGS = -Wall -Wextra -Werror
NAME = philo_bonus

RM = rm -f
SRCS = main.c parser.c observer_routine.c \
		philo_routine.c philo_routine_helper.c \
		semaphore_helper.c simulation.c utils.c
OBJS = $(SRCS:.c=.o)

%.o : %.c philo.h
	$(CC) $(CFLAGS) -c $< 

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

all : $(NAME)

clean : 
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re