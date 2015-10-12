##
## Makefile for TP1 in /home/tosi_t//Prog/C++/AbstractVm/TP
##
## Made by timothee tosi
## Login   <tosi_t@epitech.net>
##
## Started on  Mon Feb 11 16:38:42 2013 timothee tosi
## Last update Thu Nov 21 23:58:41 2013 timothee tosi
##

CC		=	g++

RM		=	rm -f

#CPPFLAGS	+=	-D_DEBUG #Comment this line for cancel debug
CPPFLAGS	+=	-Wall -Wextra# -Werror
CPPFLAGS	+=	-std=c++0x
CPPFLAGS	+=	-I../Debug -I../Defines -I../NetworkEngine -I../Packet -I../Socket
CPPFLAGS	+=	 -I../Socket/UX -I../Socket/WS

NAME1		=	Server

NAME2		=	Client


SRC1		=	src/Server.cpp				\
			../../../srcs/network/APacket.cpp	\
			../../../srcs/events/NetworkEvent.cpp

SRC2		=	src/Client.cpp				\


OBJS1		=	$(SRC1:.cpp=.o)

OBJS2		=	$(SRC2:.cpp=.o)

all:		$(NAME1) $(NAME2)

$(NAME1):	$(OBJS1)
		$(CC) $(OBJS1) -o $(NAME1) $(LDFLAGS) -lpthread

$(NAME2):	$(OBJS2)
		$(CC) $(OBJS2) -o $(NAME2) $(LDFLAGS) -lpthread

clean:
		$(RM) $(OBJS1) $(OBJS2)

fclean: 	clean
		$(RM) $(NAME1) $(NAME2)

re:		fclean all

.PHONY:		all clean fclean re
