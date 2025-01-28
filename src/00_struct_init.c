/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_struct_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:32:52 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/28 11:42:57 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_init_map(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->collectibles = 0;
	map->exits = 0;
	map->players = 0;
}

void	ft_init_config(t_config *config)
{
	int32_t	monitor_width;
	int32_t	monitor_height;

	monitor_width = 0;
	monitor_height = 0;
	mlx_get_monitor_size(0, &monitor_width, &monitor_height);
	if (monitor_width <= 0 || monitor_height <= 0)
	{
		monitor_width = 1920;
		monitor_height = 1080;
	}
	config->screen_width = monitor_width;
	config->screen_height = monitor_height;
	config->max_map_width = (uint32_t)(monitor_width / TILE_SIZE);
	config->max_map_height = (uint32_t)(monitor_height / TILE_SIZE);
}

void	ft_init_textures(t_game *game)
{
	game->textures.wall = mlx_load_png("./textures/Wall.png");
	game->textures.floor = mlx_load_png("./textures/Floor.png");
	game->textures.collectible = mlx_load_png("./textures/Collectible.png");
	game->textures.exit_closed = mlx_load_png("./textures/Exit_closed.png");
	game->textures.exit_open = mlx_load_png("./textures/Exit_open.png");
	game->textures.player_up = mlx_load_png("./textures/Player_up.png");
	game->textures.player_down = mlx_load_png("./textures/Player_down.png");
	game->textures.player_left = mlx_load_png("./textures/Player_left.png");
	game->textures.player_right = mlx_load_png("./textures/Player_right.png");
}

void	ft_init_game(t_game *game, t_map *map)
{
	game->map = map;
	game->mlx = NULL;
	game->moves = 0;
	game->player_dir = 'D';
	ft_memset(&game->textures, 0, sizeof(game->textures));
}
