/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_render_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:52:24 by amarroyo          #+#    #+#             */
/*   Updated: 2025/03/09 17:38:01 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_render_tile(t_game *game, int x, int y)
{
	char		tile;
	mlx_image_t	*img;

	tile = game->map->grid[y][x];
	img = NULL;
	if (tile == WALL)
		img = game->images.wall;
	else if (tile == EMPTY)
		img = game->images.floor;
	else if (tile == COLLECTIBLE)
		img = game->images.collectible;
	else if (tile == EXIT)
	{
		if (game->map->collectibles > 0)
			img = game->images.exit_closed;
		else
			img = game->images.exit_open;
	}
	if (img)
		mlx_image_to_window(game->mlx, img, x * TILE_SIZE, y * TILE_SIZE);
}

void	ft_render_player(t_game *game)
{
	mlx_image_t	*img;

	img = NULL;
	if (game->player_dir == 'U')
		img = game->images.player_up;
	else if (game->player_dir == 'D')
		img = game->images.player_down;
	else if (game->player_dir == 'L')
		img = game->images.player_left;
	else if (game->player_dir == 'R')
		img = game->images.player_right;
	if (img)
		mlx_image_to_window(game->mlx, img, game->map->player_x * TILE_SIZE,
			game->map->player_y * TILE_SIZE);
}

void	ft_render_map(t_game *game)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			ft_render_tile(game, x, y);
			x++;
		}
		y++;
	}
}
