# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-mezz <ael-mezz@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/13 08:14:39 by ael-mezz          #+#    #+#              #
#    Updated: 2021/10/14 10:29:15 by ael-mezz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	pipex.c			\
		pipex_utils.c

BONUS_SRCS =	pipex_bonus.c			\
				pipex_utils.c			\
				pipex_utils_bonus.c

LIBFT =	libft/libft.a

FLAGS =	-g  -Wall -Werror -Wextra #-fsanitize=address

SRCS_PATH =	./

CC = gcc

RM = rm -rf

OBJ = $(SRCS:.c=.o)

HEADER = pipex.h

SRCS := $(addprefix $(SRCS_PATH)/, $(SRCS))

BONUS_SRCS := $(addprefix $(SRCS_PATH)/, $(BONUS_SRCS))

all: $(SRCS) $(HEADER)
	@make -C libft && make bonus -C libft
	@$(CC) $(SRCS) $(LIBFT) $(FLAGS) -o pipex

bonus: $(BONUS_SRCS) $(HEADER)
	@make -C libft && make bonus -C libft
	@$(CC) $(BONUS_SRCS) -lreadline $(LIBFT) $(FLAGS) -o pipex_bonus

clean:
	@echo "cleaning..."
	@make clean -C libft
	@$(RM) pipex pipex.dSYM pipex_bonus

fclean:	clean
	@make fclean -C libft

re: fclean all exec
