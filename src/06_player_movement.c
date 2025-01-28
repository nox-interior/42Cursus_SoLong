/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_player_movement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:37:04 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/28 12:22:22 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_check_tile(t_game *game, int new_x, int new_y)
{
	if (game->map->grid[new_y][new_x] == WALL)
		return ;
	if (game->map->grid[new_y][new_x] == COLLECTIBLE)
	{
		game->map->grid[new_y][new_x] = EMPTY;
		game->map->collectibles--;
	}
	if (game->map->grid[new_y][new_x] == EXIT)
	{
		if (game->map->collectibles == 0)
		{
			ft_putstr_fd("You win!\n", 1);
			ft_exit_game(game);
		}
		return ;
	}
}

static void	ft_update_position(t_game *game, int new_x, int new_y)
{
	game->map->grid[game->map->player_y][game->map->player_x] = EMPTY;
	game->map->grid[new_y][new_x] = PLAYER;
	game->map->player_x = new_x;
	game->map->player_y = new_y;
}

static void	ft_update_direction_and_moves(t_game *game, int key)
{
	if (key == MLX_KEY_W)
		game->player_dir = 'U';
	else if (key == MLX_KEY_S)
		game->player_dir = 'D';
	else if (key == MLX_KEY_A)
		game->player_dir = 'L';
	else if (key == MLX_KEY_D)
		game->player_dir = 'R';
	game->moves++;
	ft_putnbr_fd(game->moves, 1);
	ft_putchar_fd('\n', 1);
}

void	ft_move_player(t_game *game, int dx, int dy, int key)
{
	int	new_x = game->map->player_x + dx;
	int	new_y = game->map->player_y + dy;

	ft_check_tile(game, new_x, new_y);
	if (game->map->grid[new_y][new_x] == WALL
		|| game->map->grid[new_y][new_x] == EXIT)
		return ;
	ft_update_position(game, new_x, new_y);
	ft_update_direction_and_moves(game, key);
}

void	ft_handle_keypress(mlx_key_data_t keydata, void *param)
{
	t_game	*game = (t_game *)param;

	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			ft_exit_game(game);
		else if (keydata.key == MLX_KEY_W)
			ft_move_player(game, 0, -1, MLX_KEY_W);
		else if (keydata.key == MLX_KEY_S)
			ft_move_player(game, 0, 1, MLX_KEY_S);
		else if (keydata.key == MLX_KEY_A)
			ft_move_player(game, -1, 0, MLX_KEY_A);
		else if (keydata.key == MLX_KEY_D)
			ft_move_player(game, 1, 0, MLX_KEY_D);
		ft_render_map(game);
		ft_render_player(game);
	}
}

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
	ft_putstr_fd("Exiting game.\n", 1);
	exit(EXIT_SUCCESS);
}
