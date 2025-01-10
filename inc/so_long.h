/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 08:51:40 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/10 11:49:25 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>			// open
# include <unistd.h>		// close - read - write
# include <stdlib.h>		// malloc - free -exit
# include <stdio.h>			// perror
# include <errno.h>			// perror
# include <string.h>		// strerror
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "MLX42/MLX42.h"

// Map elements
# define WALL '1'
# define EMPTY '0'
# define PLAYER 'P'
# define EXIT 'E'
# define COLLECTIBLE 'C'

// Error codes
# define ERR_FILE_OPEN 1
# define ERR_FILE_READ 2
# define ERR_INVALID_MAP 3
# define ERR_MALLOC 4

// Tile size in pixels (industry standard)
# define TILE_SIZE 32

// Structure(s)
/* Map struture*/
typedef struct s_map
{
	char		**grid;			// 2D array for the map layout
	uint32_t	width;			// Width of the map (columns)
	uint32_t	height;			// Height of the map (rows)
	int			player_x;		// Player's X position
	int			player_y;		// Player's Y position
	uint32_t	collectibles;	// Count of collectibles
	uint32_t	exits;			// Number of exits
	uint32_t	players;		// Number of players (should be 1)
}				t_map;

/* game Structure*/
typedef struct s_game
{
	t_map		*map;			// Pointer to the map structure
	mlx_t		*mlx;			// MLX42 instance (includes the window)
	uint32_t	moves;			// Number of moves made by the player
}				t_game;

// Error codes
typedef enum e_error
{
	ERR_NONE,
	ERR_EXTENSION_INVALID,
	ERR_MAP_INVALID,
	ERR_MISSING_PLAYER,
	ERR_MISSING_EXIT,
	ERR_MISSING_COLLECTIBLES,
	ERR_FILE_PATH_INVALID,	
	ERR_OPEN_FILE,
	ERR_READ_FILE,	
	ERR_SYSTEM						// System-level error use perror or strerror
}			t_error;

// Functions
t_error	ft_check_extension(const char *str);
void	ft_system_error_handling(t_error error_code, const char *ctxt);
void	ft_map_error_handling(t_error error_code);
void	ft_error_handling(t_error error_code, const char *ctxt);
int	ft_open_map_file(const char *file_path);
t_error	ft_read_map_lines(int fd, t_map *map);
int	main(int argc, char **argv);

#endif