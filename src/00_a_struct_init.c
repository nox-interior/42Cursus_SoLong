/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_a_struct_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:32:52 by amarroyo          #+#    #+#             */
/*   Updated: 2025/03/09 16:50:52 by amarroyo         ###   ########.fr       */
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

	monitor_width = 3840;
	monitor_height = 2096;
	config->screen_width = monitor_width;
	config->screen_height = monitor_height;
	config->max_map_width = (uint32_t)(monitor_width / TILE_SIZE);
	config->max_map_height = (uint32_t)(monitor_height / TILE_SIZE);
}

void	ft_init_game(t_game *game, t_map *map)
{
	game->map = map;
	game->mlx = NULL;
	game->moves = 0;
	game->player_dir = 'D';
	ft_memset(&game->textures, 0, sizeof(game->textures));
	ft_memset(&game->images, 0, sizeof(game->images));
}
