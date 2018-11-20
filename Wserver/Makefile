CC		= 	gcc
NAME 	= 	server
SRC		= 	functions.c \
			ddw.c \
			main.c

OBJ 	= 	$(SRC:%.c=%.o)
CFLAGS	= 	-W -Wall -Werror
LIB		= 	-lzmq -lczmq -lpthread

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) $(LIB)

all:	$(NAME)

.PHONY:	clean

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM)	$(NAME)

re:	fclean all
