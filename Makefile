# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/30 08:41:33 by amarroyo          #+#    #+#              #
#    Updated: 2024/12/30 12:28:59 by amarroyo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Standard
NAME			= so_long

# Directories
LIBFT			= libft/libft.a
MLX				= mlx/mlxbuild/libmlx42.a
MLX_DIR			= mlx
INC_DIR         = inc/
SRC_DIR         = src/
OBJ_DIR         = obj/

# Compiler and Flags
CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -I$(INC_DIR) -I$(MLX)
MLX_FLAGS		= -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz
rm				= rm -f
# instrucciones para compilar la lib de CODAM, por el momento no sé si 
# es necesario modificar esto.
# gcc main.c ... libmlx42.a -Iinclude -ldl -lglfw -pthread -lm


# Source Files
SRC				= $(wildcard $(SRC_DIR)*.c) # Temporary placeholder
OBJ				= $(SRC_FILES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# Build rules
all:			$(NAME)

$(LIBFT):
	@make -C ./libft

$(MLX):
	@make -C ./mlx

# Building the executable
$(NAME):		$(OBJ) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIBFT) $(MLX_FLAGS) $(MLX) -o $(NAME)

# Compile object files from source files
$(OBJ_DIR)%.o: 	$(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@



# Clean object files
clean:
	@$(RM) -r $(OBJ_DIR)
	@make clean -C $(LIBFT)
	@make clean -C $(MLX)

# Clean object files and executable
fclean:			clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)
	@$(RM) $(MLX)

# Rebuild everything
re:				fclean all

# Phony targets
.PHONY:			all clean fclean re
