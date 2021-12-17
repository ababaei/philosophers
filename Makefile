# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/05 01:57:11 by ababaei           #+#    #+#              #
#    Updated: 2021/12/17 14:12:05 by ababaei          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

PHILO_SRC = main.c \
			parser.c \
			init.c \
			ft_strtol.c \
			utils.c \
			thread.c

PHILO_OBJ = $(PHILO_SRC:.c=.o)

DIROBJ = objs/

DIROBJS = $(addprefix $(DIROBJ), $(PHILO_OBJ))

FLAGS = -Wall -g -Wextra -Werror -fsanitize=thread

NAME = philo

all:$(NAME)

$(DIROBJ)%.o: %.c
	@mkdir -p $(DIROBJ)
	@echo compiling: $<
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME):$(DIROBJS)
	@echo Creating executable $(NAME)	
	@$(CC) -pthread $(DIROBJ)*.o $(FLAGS) -o $(NAME)

clean:
	rm -rf $(DIROBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
