/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_render_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:52:24 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/28 15:09:06 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_render_tile(t_game *game, int x, int y)
{
	char			tile;
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	tile = game->map->grid[y][x];
	texture = NULL;
	if (tile == WALL)
		texture = game->textures.wall;
	else if (tile == EMPTY)
		texture = game->textures.floor;
	else if (tile == COLLECTIBLE)
		texture = game->textures.collectible;
	else if (tile == EXIT)
	{
		if (game->map->collectibles > 0)
			texture = game->textures.exit_closed;
		else
			texture = game->textures.exit_open;
	}
	if (texture)
	{
		img = mlx_texture_to_image(game->mlx, texture);
		if (img)
			mlx_image_to_window(game->mlx, img, x * TILE_SIZE, y * TILE_SIZE);
	}
}

void	ft_render_player(t_game *game)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = NULL;
	if (game->player_dir == 'U')
		texture = game->textures.player_up;
	else if (game->player_dir == 'D')
		texture = game->textures.player_down;
	else if (game->player_dir == 'L')
		texture = game->textures.player_left;
	else if (game->player_dir == 'R')
		texture = game->textures.player_right;
	if (texture)
	{
		img = mlx_texture_to_image(game->mlx, texture);
		if (img)
			mlx_image_to_window(game->mlx, img,
				game->map->player_x * TILE_SIZE,
				game->map->player_y * TILE_SIZE);
	}
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

void	ft_exit_game(t_game *game)
{
	if (game->textures.wall)
		mlx_delete_texture(game->textures.wall);
	if (game->textures.floor)
		mlx_delete_texture(game->textures.floor);
	if (game->textures.collectible)
		mlx_delete_texture(game->textures.collectible);
	if (game->textures.exit_closed)
		mlx_delete_texture(game->textures.exit_closed);
	if (game->textures.exit_open)
		mlx_delete_texture(game->textures.exit_open);
	if (game->textures.player_up)
		mlx_delete_texture(game->textures.player_up);
	if (game->textures.player_down)
		mlx_delete_texture(game->textures.player_down);
	if (game->textures.player_left)
		mlx_delete_texture(game->textures.player_left);
	if (game->textures.player_right)
		mlx_delete_texture(game->textures.player_right);
	ft_free_map_grid(game->map->grid, game->map->height);
	if (game->mlx)
		mlx_terminate(game->mlx);
	free(game->map);
	ft_putstr_fd("Exiting game.\n", 1);
	exit(EXIT_SUCCESS);
}
