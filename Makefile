# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-mezz <ael-mezz@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/13 08:14:39 by ael-mezz          #+#    #+#              #
#    Updated: 2021/10/12 16:51:48 by ael-mezz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	pipex.c			\
		pipex_utils.c

LIBFT =	libft/libft.a

FLAGS =	-g  -Wall -Werror -Wextra #-fsanitize=address

SRCS_PATH =	./

CC = gcc

RM = rm -rf

OBJ = $(SRCS:.c=.o)

OBJ_DIR = mv *.o srcs

HEADER = pipex.h

SRCS := $(addprefix $(SRCS_PATH)/, $(SRCS))

all: $(SRCS) $(HEADER)
	@make -C libft && make bonus -C libft
	@$(CC) $(SRCS) $(LIBFT) $(FLAGS) -o pipex

clean:
	@echo "cleaning..."
	@make clean -C libft
	@$(RM) pipex pipex.dSYM

fclean:	clean
	@make fclean -C libft


re: fclean all exec
