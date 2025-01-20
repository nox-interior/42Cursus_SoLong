/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_struct_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:32:52 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/20 13:19:21 by amarroyo         ###   ########.fr       */
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
	map->players = 0;
	map->exits = 0;
	map->collectibles = 0;
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
