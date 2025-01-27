/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:00:06 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/27 17:03:54 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->map->player_x + dx;
	new_y = game->map->player_y + dy;
	if (game->map->grid[new_y][new_x] == WALL)
		return ;
	if (game->map->grid[new_y][new_x] == COLLECTIBLE)
	{
		if (game->map->grid[new_y][new_x] == COLLECTIBLE)
		{
			game->map->grid[new_y][new_x] = EMPTY;
			if (game->map->collectibles > 0)
				game->map->collectibles--;
			ft_render_map(game);
		}
		if (game->map->grid[new_y][new_x] == EXIT)
		{
			if (game->map->collectibles == 0)
			{
				ft_putstr_fd("You win!\n", 1);
				ft_exit_game(game);
			}
			else
				return ;
		}
	}
	// Update grid and player's position
	game->map->grid[game->map->player_y][game->map->player_x] = EMPTY;
	game->map->grid[new_y][new_x] = PLAYER;
	game->map->player_x = new_x;
	game->map->player_y = new_y;

	// Update player direction
	if (dx == 0 && dy == -1)
		game->player_dir = 'U';
	else if (dx == 0 && dy == 1)
		game->player_dir = 'D';
	else if (dx == -1 && dy == 0)
		game->player_dir = 'L';
	else if (dx == 1 && dy == 0)
		game->player_dir = 'R';

	// Update move counter
	game->moves++;
	ft_putnbr_fd(game->moves, 1);
	ft_putstr_fd("\n", 1);
}

mlx_image_t	*ft_get_player_tile(t_game *game)
{
	if (game->player_dir == 'U')
		return (mlx_texture_to_image(game->mlx, game->textures.player_up));
	if (game->player_dir == 'D')
		return (mlx_texture_to_image(game->mlx, game->textures.player_down));
	if (game->player_dir == 'L')
		return (mlx_texture_to_image(game->mlx, game->textures.player_left));
	if (game->player_dir == 'R')
		return (mlx_texture_to_image(game->mlx, game->textures.player_right));
	return (NULL);
}

mlx_image_t	*ft_select_tile_image(t_game *game, int x, int y)
{
	char	tile;

	tile = game->map->grid[y][x];
	if (tile == WALL)
		return (mlx_texture_to_image(game->mlx, game->textures.wall));
	if (tile == EMPTY)
		return (mlx_texture_to_image(game->mlx, game->textures.floor));
	if (tile == COLLECTIBLE)
		return (mlx_texture_to_image(game->mlx, game->textures.collectible));
	if (tile == EXIT)
	{
		if (game->map->collectibles == 0)
			return (mlx_texture_to_image(game->mlx, game->textures.exit_open));
		else
			return (mlx_texture_to_image(game->mlx, game->textures.exit_closed));
	}
	if (x == game->map->player_x && y == game->map->player_y)
		return (ft_get_player_tile(game));
	return (NULL);
}

void	ft_free_textures(t_game *game)
{
	mlx_delete_texture(game->textures.wall);
	mlx_delete_texture(game->textures.floor);
	mlx_delete_texture(game->textures.collectible);
	mlx_delete_texture(game->textures.exit_closed);
	mlx_delete_texture(game->textures.exit_open);
	mlx_delete_texture(game->textures.player_up);
	mlx_delete_texture(game->textures.player_down);
	mlx_delete_texture(game->textures.player_left);
	mlx_delete_texture(game->textures.player_right);
}

void	ft_handle_movement(int key, t_game *game)
{
	if (key == MLX_KEY_W)
		ft_move_player(game, 0, -1);
	else if (key == MLX_KEY_S)
		ft_move_player(game, 0, 1);
	else if (key == MLX_KEY_A)
		ft_move_player(game, -1, 0);
	else if (key == MLX_KEY_D)
		ft_move_player(game, 1, 0);
}
void	ft_handle_keypress(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		ft_exit_game(game);
	if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S
			|| keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D)
		&& keydata.action == MLX_PRESS)
	{
		ft_handle_movement(keydata.key, game);
		ft_render_map(game);
	}
}

void ft_exit_game(t_game *game)
{
	ft_free_textures(game);
	if (game->map)
	{
		ft_free_map_grid(game->map->grid, game->map->height);
		free(game->map);
	}
	if (game->mlx)
		mlx_terminate(game->mlx);
	exit(EXIT_SUCCESS);
}

void	ft_render_tile(t_game *game, int x, int y)
{
	char		tile;
	mlx_texture_t	*texture;

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
		if (game->map->collectibles == 0)

			texture = game->textures.exit_open;	
		else
			texture = game->textures.exit_closed;
	}
	if (texture)
	{
		mlx_image_t *img = mlx_texture_to_image(game->mlx, texture);
		if (img)
			mlx_image_to_window(game->mlx, img, x * TILE_SIZE, y * TILE_SIZE);
	}
}

void	ft_render_player(t_game *game)
{
	mlx_texture_t	*texture;

	if (game->player_dir == 'U')
		texture = game->textures.player_up;
	else if (game->player_dir == 'D')
		texture = game->textures.player_down;
	else if (game->player_dir == 'L')
		texture = game->textures.player_left;
	else
		texture = game->textures.player_right;

	if (texture)
	{
		mlx_image_t *img = mlx_texture_to_image(game->mlx, texture);
		if (img)
			mlx_image_to_window(
				game->mlx,
				img,
				game->map->player_x * TILE_SIZE,
				game->map->player_y * TILE_SIZE
			);
	}
}

void	ft_render_map(t_game *game)
{
	uint32_t	x;
	uint32_t	y;
	mlx_image_t	*img;

	printf("Rendering map\n"); //Debugging
	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			img = ft_select_tile_image(game, x, y);
			if (img)
				mlx_image_to_window(game->mlx, img, x * TILE_SIZE, y
					* TILE_SIZE);
			x++;
		}
		y++;
	}
}
