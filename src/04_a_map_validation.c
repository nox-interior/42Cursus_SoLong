/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_a_map_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:47:41 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/29 11:32:43 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_error	ft_validate_dimensions(t_map *map)
{
	if (map->width < 3 || map->height < 3)
		return (ERR_MAP_INVALID);
	return (ERR_NONE);
}

static t_error	ft_validate_boundaries(t_map *map)
{
	uint32_t	row;

	row = 0;
	while (row < map->width)
	{
		if (map->grid[0][row] != WALL || map->grid[map->height - 1]
			[row] != WALL)
			return (ERR_MAP_INVALID);
		row++;
	}
	row = 1;
	while (row < map->height - 1)
	{
		if (map->grid[row][0] != WALL || map->grid[row][map->width - 1] != WALL)
			return (ERR_MAP_INVALID);
		row++;
	}
	return (ERR_NONE);
}

t_error	ft_validate_screen_limit(t_map *map, t_config *config)
{
	if (map->width > config->max_map_width
		|| map->height > config->max_map_height)
		return (ERR_SCREEN_LIMIT);
	return (ERR_NONE);
}

t_error	ft_validate_map(t_map *map)
{
	t_error	error;

	error = ft_validate_dimensions(map);
	if (error != ERR_NONE)
		return (error);
	error = ft_validate_boundaries(map);
	if (error != ERR_NONE)
		return (error);
	error = ft_validate_characters(map);
	if (error != ERR_NONE)
		return (error);
	return (ERR_NONE);
}
