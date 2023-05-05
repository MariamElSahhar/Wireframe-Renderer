# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/03 17:06:15 by melsahha          #+#    #+#              #
#    Updated: 2023/05/05 16:12:12 by melsahha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
INCL = ./include/
CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX = minilibx_macos
LIBFT_DIR = libft/
LIBFT = libftprintf.a

SRC_DIR = src/
OBJ_DIR = obj

SRC = $(addprefix $(SRC_DIR), main.c draw.c grid.c fdf.c events.c coords.c get_next_line.c get_next_line_utils.c)
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

$(NAME): $(LIBFT) $(OBJ) $(OBJ_DIR)
	$(CC) -L $(MLX) -lmlx -framework OpenGL -framework AppKit $(OBJ) $(LIBFT) -o $(NAME)

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) -I$(INCL) -I $(MLX) $< -o $@

$(OBJ_DIR):
	mkdir -p $@

$(LIBFT):
	make -C $(LIBFT_DIR)
	mv $(addprefix $(LIBFT_DIR), $(LIBFT)) .

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(LIBFT)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette *.c *.h -R CheckDefine
	norminette $(addprefix $(PRINTF_DIR), *.c) $(addprefix $(PRINTF_DIR), *.h) -R CheckDefine
	norminette $(addprefix $(GNL_DIR), *.h) -R CheckDefine
	norminette $(addprefix $(LIBFT_DIR), *.c) $(addprefix $(LIBFT_DIR), *.h) -R CheckDefine

.phony: re clean fclean all norm
