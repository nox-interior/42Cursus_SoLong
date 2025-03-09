/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_end_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:35:55 by amarroyo          #+#    #+#             */
/*   Updated: 2025/03/09 17:38:16 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_delete_textures(t_textures *textures)
{
	if (textures->wall)
		mlx_delete_texture(textures->wall);
	if (textures->floor)
		mlx_delete_texture(textures->floor);
	if (textures->collectible)
		mlx_delete_texture(textures->collectible);
	if (textures->exit_closed)
		mlx_delete_texture(textures->exit_closed);
	if (textures->exit_open)
		mlx_delete_texture(textures->exit_open);
	if (textures->player_up)
		mlx_delete_texture(textures->player_up);
	if (textures->player_down)
		mlx_delete_texture(textures->player_down);
	if (textures->player_left)
		mlx_delete_texture(textures->player_left);
	if (textures->player_right)
		mlx_delete_texture(textures->player_right);
}

static void	ft_delete_images(t_game *game)
{
	if (game->images.wall)
		mlx_delete_image(game->mlx, game->images.wall);
	if (game->images.floor)
		mlx_delete_image(game->mlx, game->images.floor);
	if (game->images.collectible)
		mlx_delete_image(game->mlx, game->images.collectible);
	if (game->images.exit_closed)
		mlx_delete_image(game->mlx, game->images.exit_closed);
	if (game->images.exit_open)
		mlx_delete_image(game->mlx, game->images.exit_open);
	if (game->images.player_up)
		mlx_delete_image(game->mlx, game->images.player_up);
	if (game->images.player_down)
		mlx_delete_image(game->mlx, game->images.player_down);
	if (game->images.player_left)
		mlx_delete_image(game->mlx, game->images.player_left);
	if (game->images.player_right)
		mlx_delete_image(game->mlx, game->images.player_right);
}

void	ft_exit_game(t_game *game)
{
	ft_delete_textures(&game->textures);
	ft_delete_images(game);
	ft_free_map_grid(game->map->grid, game->map->height);
	if (game->mlx)
		mlx_terminate(game->mlx);
	free(game->map);
	ft_putstr_fd("Exiting game.\n", 1);
	exit(EXIT_SUCCESS);
}
