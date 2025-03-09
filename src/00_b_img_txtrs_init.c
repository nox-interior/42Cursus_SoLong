/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_b_img_txtrs_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:50:12 by amarroyo          #+#    #+#             */
/*   Updated: 2025/03/09 17:31:46 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_load_textures(t_textures *textures)
{
	textures->wall = mlx_load_png("./textures/Wall.png");
	textures->floor = mlx_load_png("./textures/Floor.png");
	textures->collectible = mlx_load_png("./textures/Collectible.png");
	textures->exit_closed = mlx_load_png("./textures/Exit_closed.png");
	textures->exit_open = mlx_load_png("./textures/Exit_open.png");
	textures->player_up = mlx_load_png("./textures/Player_up.png");
	textures->player_down = mlx_load_png("./textures/Player_down.png");
	textures->player_left = mlx_load_png("./textures/Player_left.png");
	textures->player_right = mlx_load_png("./textures/Player_right.png");
}

t_error	ft_verify_textures(t_textures *textures)
{
	if (!textures->wall || !textures->floor || !textures->collectible
		|| !textures->exit_closed || !textures->exit_open
		|| !textures->player_up || !textures->player_down
		|| !textures->player_left || !textures->player_right)
		return (ERR_TEXTURE_LOAD);
	return (ERR_NONE);
}

static void	ft_create_images(t_game *game)
{
	game->images.wall = mlx_texture_to_image(game->mlx, game->textures.wall);
	game->images.floor = mlx_texture_to_image(game->mlx, game->textures.floor);
	game->images.collectible = mlx_texture_to_image(game->mlx,
			game->textures.collectible);
	game->images.exit_closed = mlx_texture_to_image(game->mlx,
			game->textures.exit_closed);
	game->images.exit_open = mlx_texture_to_image(game->mlx,
			game->textures.exit_open);
	game->images.player_up = mlx_texture_to_image(game->mlx,
			game->textures.player_up);
	game->images.player_down = mlx_texture_to_image(game->mlx,
			game->textures.player_down);
	game->images.player_left = mlx_texture_to_image(game->mlx,
			game->textures.player_left);
	game->images.player_right = mlx_texture_to_image(game->mlx,
			game->textures.player_right);
}

t_error	ft_verify_images(t_game *game)
{
	if (!game->images.wall || !game->images.floor || !game->images.collectible
		|| !game->images.exit_closed || !game->images.exit_open
		|| !game->images.player_up || !game->images.player_down
		|| !game->images.player_left || !game->images.player_right)
		return (ERR_IMG_CREATION);
	return (ERR_NONE);
}

void	ft_init_textures(t_game *game)
{
	ft_load_textures(&game->textures);
	if (ft_verify_textures(&game->textures) != ERR_NONE)
	{
		ft_error_handling(ERR_TEXTURE_LOAD, NULL);
		exit(EXIT_FAILURE);
	}
	ft_create_images(game);
	if (ft_verify_images(game) != ERR_NONE)
	{
		ft_error_handling(ERR_IMG_CREATION, NULL);
		exit(EXIT_FAILURE);
	}
}
