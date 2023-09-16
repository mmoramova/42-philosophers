# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/25 13:17:12 by mmoramov          #+#    #+#              #
#    Updated: 2023/09/16 15:34:36 by mmoramov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo
HEADER = philo.h
C_FLAGS = -Wall -Wextra -Werror -MMD
#-lpthread
RM = rm -f

# Colors
BLACK = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SRC_FILES = philo philo_init philo_utils philo_timeutils

SRC = $(addsuffix .c, $(SRC_FILES))
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

all: $(NAME)

-include ${DEP}

%.o: %.c
	$(CC) $(C_FLAGS) -c $< -o $@

$(NAME):: $(OBJ)
	$(CC) $(C_FLAGS) $(^) -o $(NAME)
	@echo "$(BLUE)Everything has been compilated.$(BLACK)"

$(NAME)::
	@echo "$(BLUE)No actions needed.$(BLACK)"

.PHONY: all clean fclean re

clean:
	$(RM) $(OBJ) $(DEP)

fclean: clean
	$(RM) $(NAME)
	@echo "$(MAGENTA)Everything has been cleaned.$(BLACK)"

re: fclean all
