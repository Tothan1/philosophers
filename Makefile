#### VARIABLES ####
NAME = philo
# HEADER_PATH = include
CC= cc
# CFLAGS=-Wall -Wextra -Werror -I $(HEADER0_PATH)
CFLAGS=-Wall -Wextra -Werror -pthread
# OBJ=ft_*.c =.o
# SRCS = $(HEADER_PATH)ft_atoi
#### SOURCE ####
SRC_FILES = main.c

OBJ_FILES = $(SRC_FILES:.c=.o)
# OBJ_FILES = $(addsuffix .o, $(SRC_FILES))
#### RULES ####
all: ${NAME}


${NAME} :${OBJ_FILES} 
	${CC} ${CFLAGS} -o ${NAME} ${OBJ_FILES}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@ -g3

clean:
	rm -f ${OBJ_FILES}

fclean: clean
	rm -f ${NAME}

val: all clean
	valgrind --leak-check=full ./${NAME} "4 1 3 0 2"

re: fclean  all

.PHONY: all clean fclean re 
