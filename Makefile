# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 10:42:37 by amarroyo          #+#    #+#              #
#    Updated: 2025/01/15 15:41:25 by amarroyo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Standard
NAME = so_long

# Directories
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = mlx
MLX_BUILD_DIR = $(MLX_DIR)/mlxbuild
MLX_LIB = $(MLX_BUILD_DIR)/libmlx42.a
INC_DIR = inc/
SRC_DIR = src/
OBJ_DIR = obj/

# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(MLX_DIR)/include -I$(LIBFT_DIR)/inc
MLX_FLAGS = -L$(MLX_BUILD_DIR) -lmlx42 -I$(MLX_DIR)/include -ldl -lglfw -pthread -lm
RM = rm -rf

# Source and Object Files
SRC = 	$(SRC_DIR)00_struct_init.c \
		$(SRC_DIR)01_extension_validation.c \
		$(SRC_DIR)02_error_handling.c \
		$(SRC_DIR)03_a_file_parsing.c \
		$(SRC_DIR)03_b_file_parsing.c \
		$(SRC_DIR)04_grid_handling.c \
		$(SRC_DIR)05_a_map_validation.c \
		$(SRC_DIR)05_b_map_validation.c \
		$(SRC_DIR)main.c \
		
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Targets
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX_LIB)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "Compiled $(NAME) successfully!"

$(LIBFT):
	@make -C $(LIBFT_DIR)
	@echo "Built libft library."

$(MLX_LIB):
	@mkdir -p $(MLX_BUILD_DIR)
	@cmake -S $(MLX_DIR) -B $(MLX_BUILD_DIR)
	@cmake --build $(MLX_BUILD_DIR) -j4
	@echo "Built MLX42 library in $(MLX_BUILD_DIR)."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $< into $@"

clean:
	@$(RM) $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@echo "Cleaned object files and libft."

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(MLX_BUILD_DIR)
	@echo "Fully cleaned the project, including MLX42."

re: fclean all

.PHONY: all clean fclean re