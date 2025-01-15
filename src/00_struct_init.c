/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_struct_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:32:52 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/15 16:40:01 by amarroyo         ###   ########.fr       */
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
