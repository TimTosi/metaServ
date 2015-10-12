CC		=	g++

RM		=	rm -f

CPPFLAGS	+=	-Wall -Wextra# -Werror
CPPFLAGS	+=	-std=c++0x
CPPFLAGS	+=	-I../../include/concurrency

NAME		=	ThreadTest

SRC			=	main.cpp								\
				../../src/concurrency/Thread.cpp 		\
				../../src/concurrency/Mutex.cpp 		\
				../../src/concurrency/ScopedLock.cpp	\

OBJS		=	$(SRC:.cpp=.o)



all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) -lpthread

clean:
		$(RM) $(OBJS)

fclean: 	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
