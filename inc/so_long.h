/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:08:54 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/20 17:13:33 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
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

// Tile size (px)
# define TILE_SIZE 32

// Structures
/* Map structure*/
typedef struct s_map
{
	char		**grid;
	uint32_t	width;
	uint32_t	height;
	int			player_x;
	int			player_y;
	uint32_t	collectibles;
	uint32_t	exits;
	uint32_t	players;
}				t_map;

/* Game structure*/
typedef struct s_game
{
	t_map		*map;
	mlx_t		*mlx;
	uint32_t	moves;
}				t_game;

/*Configuration structure for dynamic limits*/
typedef struct s_config
{
	int	screen_width;
	int	screen_height;
	uint32_t	max_map_width;
	uint32_t	max_map_height;
}				t_config;

/* Flood fill*/
typedef struct s_point
{
	int	x;
	int	y; 
}				t_point;

// Error codes
typedef enum e_error
{
	ERR_NONE,
	ERR_EXTENSION_INVALID,
	ERR_MAP_INVALID,
	ERR_PLAYER,
	ERR_EXIT,
	ERR_MISSING_COLLECTIBLES,
	ERR_FILE_PATH_INVALID,
	ERR_OPEN_FILE,
	ERR_READ_FILE,
	ERR_PATH_INVALID,
	ERR_SCREEN_LIMIT,
	ERR_SYSTEM
}				t_error;

// Functions
t_error	ft_check_extension(const char *str);
void	ft_system_error_handling(t_error error_code, const char *ctxt);
void	ft_map_error_handling(t_error error_code);
void	ft_error_handling(t_error error_code, const char *ctxt);
int		ft_open_map_file(const char *file_path);
void	ft_initialize_grid(char **grid, int size);
char	**ft_allocate_grid(int size);
t_error	ft_parse_map(const char *file_path, t_map *map, t_config *config);
t_error	ft_process_line(char *line, t_map *map, int line_count);
t_error ft_read_map_lines(int fd, t_map *map, t_config *config);
//t_error	ft_read_map_lines(int fd, t_map *map);
void	ft_free_map_grid(char **grid, int line_count);
t_error	ft_validate_characters(t_map *map);
t_error	ft_validate_screen_limit(t_map *map, t_config *config);
t_error	ft_validate_map(t_map *map);
char	**ft_duplicate_grid(char **grid, uint32_t height);
void	ft_flood_fill(t_map *map, char **grid, int y, int x);
t_error	ft_validate_path(t_map *map);
void	ft_init_map(t_map *map);
void	ft_init_config(t_config *config);
int		main(int argc, char **argv);

#endif