# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvarela <rvarela@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/12 12:23:29 by rvarela           #+#    #+#              #
#    Updated: 2024/05/12 12:23:32 by rvarela          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CFLAGS = -Wall -Werror -Wextra -g
LIBFLAGS = ar -rcs
MKFLAG = --no-print-directory

SRC_DIR = src

INC_DIR = includes

LIBFT = libft/libft.a
LIBFT_DIR = libft

SRC = main.c

OBJ = $(addprefix $(SRC_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	cc $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	cc $(CFLAGS) -c $< -I $(INC_DIR) -o $@

$(LIBFT):
	$(MAKE) $(MKFLAG) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ)
	$(MAKE) $(MKFLAG) clean -C $(LIBFT_DIR)
	
fclean: clean
	rm -rf $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re