CC = clang
CFLAGS = -Wall -Wextra -Werror
NAME = philo

RM = rm -f
SRCS = main.c mutex_helper.c observer_routine.c parser.c utils.c \
		philo_arg_helper.c philo_routine.c philo_routine_helper.c \
		simulation.c 
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