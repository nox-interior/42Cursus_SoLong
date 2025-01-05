# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I ../mlx/include

# Source files and output
SRC = colours_example_02.c
OBJ = $(SRC:.c=.o)
NAME = colours_example_program_02

# MLX42 library paths
LIB_MLX = ../mlx
MLX_LIB = $(LIB_MLX)/mlxbuild/libmlx42.a
MLX_FLAGS = -L$(LIB_MLX)/mlxbuild -lmlx42 -ldl -lglfw -pthread

# Default rule
all: $(NAME)

# Build the executable
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(MLX_LIB) $(MLX_FLAGS)

# Object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rules
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Build the MLX42 library if it doesn't exist
$(MLX_LIB):
	cd $(LIB_MLX) && cmake -B mlxbuild && cmake --build mlxbuild -j4