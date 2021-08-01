PHILO		= philo

CFLAGS		= -Wall -Wextra -Werror

CC			= gcc

HEADER		= philo.h

RM			= rm -f

SRCS		= main.c threads.c utils.c print.c


OBJS 		= ${SRCS:.c=.o}

all: 		${PHILO}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(PHILO): 	$(OBJS)
			$(CC) $(OBJS) $(CFLAGS)  -o $(PHILO)

clean:
			${RM} ${OBJS}

fclean: 	clean
			${RM} ${PHILO}

re: 		fclean all

.PHONY:		all clean fclean re