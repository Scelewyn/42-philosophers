# COLORS
GREEN	= \033[0;32m
RED 	= \033[0;31m
ORANGE	= \033[0;33m
CYAN	= \033[0;36m
RESET	= \033[0m

SRC_DIR	= ./srcs/
SRC_FILES	=  philosophers.c philo_life.c init.c threads.c utils.c philo_life_utils.c

SRC			= ${addprefix ${SRC_DIR}, ${SRC_FILES}}
OBJ			= ${SRC:.c=.o}


THREADS		= -pthread
NAME		= philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -fsanitize=thread -g3

%.o: %.c
	@${CC} -c ${CFLAGS} ${THREADS} $< -o $@

all: ${NAME}

#Compile normal executable
${NAME}: ${OBJ}
	@${CC} ${CFLAGS} -o ${NAME} ${OBJ}
	@echo "[$(ORANGE)$(NAME)$(RESET)] Creation *.o files & compilation : $(GREEN)OK$(RESET)"
	@echo "[\033[1;32msuccess$(RESET)]: $(NAME) is ready"

clean:
	@${RM} ${OBJ}
	@echo "[$(ORANGE)$(NAME)$(RESET)] clean *.o files : $(GREEN)OK$(RESET)"

fclean:	clean
	@${RM} ${NAME}
	@${RM} -r ${NAME}.dSYM
	@echo "[$(ORANGE)$(NAME)$(RESET)] fclean: $(GREEN)OK$(RESET)"
	@echo "[\033[1;32msuccess$(RESET)]: $(NAME) has been clean up"

re: fclean all

.PHONY: all clean fclean re debug valgrind