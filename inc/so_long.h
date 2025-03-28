/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:08:54 by amarroyo          #+#    #+#             */
/*   Updated: 2025/03/24 12:30:45 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42/MLX42.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// Map elements
# define WALL '1'
# define EMPTY '0'
# define PLAYER 'P'
# define EXIT 'E'
# define COLLECTIBLE 'C'

// Tile size (px)
# define TILE_SIZE 64

// Structures
/* Map structure*/
typedef struct s_map
{
	char			**grid;
	uint32_t		width;
	uint32_t		height;
	int				player_x;
	int				player_y;
	uint32_t		collectibles;
	uint32_t		exits;
	uint32_t		players;
}					t_map;

/* Textures structure*/
typedef struct s_textures
{
	mlx_texture_t	*wall;
	mlx_texture_t	*floor;
	mlx_texture_t	*collectible;
	mlx_texture_t	*exit_closed;
	mlx_texture_t	*exit_open;
	mlx_texture_t	*player_up;
	mlx_texture_t	*player_down;
	mlx_texture_t	*player_left;
	mlx_texture_t	*player_right;
}					t_textures;

/*Images structure*/
typedef struct s_images
{
	mlx_image_t		*wall;
	mlx_image_t		*floor;
	mlx_image_t		*collectible;
	mlx_image_t		*exit_closed;
	mlx_image_t		*exit_open;
	mlx_image_t		*player_up;
	mlx_image_t		*player_down;
	mlx_image_t		*player_left;
	mlx_image_t		*player_right;
}					t_images;

/* Game structure*/
typedef struct s_game
{
	t_map			*map;
	mlx_t			*mlx;
	uint32_t		moves;
	t_textures		textures;
	t_images		images;
	char			player_dir;
}					t_game;

/* Flood fill helper structures*/
typedef struct s_reachable
{
	uint32_t		collectibles;
	uint32_t		exits;
}					t_reachable;

typedef struct s_flood
{
	t_map			*map;
	t_reachable		reachable;
}					t_flood;

/*Configuration structure for dynamic limits*/
typedef struct s_winconfig
{
	int				screen_width;
	int				screen_height;
	uint32_t		max_map_width;
	uint32_t		max_map_height;
}					t_winconfig;

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
	ERR_TEXTURE_LOAD,
	ERR_IMG_CREATION,
	ERR_SYSTEM
}					t_error;

// Functions
t_error				ft_check_extension(const char *str);
void				ft_system_error_handling(t_error error_code,
						const char *ctxt);
void				ft_map_error_handling(t_error error_code);
void				ft_error_handling(t_error error_code, const char *ctxt);
void				ft_initialize_grid(char **grid, int max_height);
char				**ft_allocate_grid(int max_height);
t_error				ft_parse_map(const char *file_path, t_map *map,
						t_winconfig *winconfig);
t_error				ft_read_map_lines(int fd, t_map *map,
						t_winconfig *winconfig);
void				ft_free_map_grid(char **grid, int line_count);
t_error				ft_validate_characters(t_map *map);
t_error				ft_validate_screen_limit(t_map *map,
						t_winconfig *winconfig);
t_error				ft_validate_map(t_map *map);
char				**ft_duplicate_grid(char **grid, uint32_t height);
void				ft_flood_fill(t_flood *flood, char **grid, int y, int x);
t_error				ft_validate_path(t_map *map);
void				ft_init_map(t_map *map);
void				ft_init_winconfig(t_winconfig *winconfig);
t_error				ft_verify_textures(t_textures *textures);
t_error				ft_verify_images(t_game *game);
void				ft_init_textures(t_game *game);
void				ft_init_game(t_game *game, t_map *map);
void				ft_move_player(t_game *game, int dx, int dy, int key);
void				ft_handle_keypress(mlx_key_data_t keydata, void *param);
void				ft_render_tile(t_game *game, int x, int y);
void				ft_render_player(t_game *game);
void				ft_render_map(t_game *game);
void				ft_exit_game(t_game *game);
int					main(int argc, char **argv);

#endif