/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_player_movement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:37:04 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/28 15:32:54 by amarroyo         ###   ########.fr       */
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
	int	new_x;
	int	new_y;

	new_x = game->map->player_x + dx;
	new_y = game->map->player_y + dy;
	ft_check_tile(game, new_x, new_y);
	if (game->map->grid[new_y][new_x] == WALL
		|| game->map->grid[new_y][new_x] == EXIT)
		return ;
	ft_update_position(game, new_x, new_y);
	ft_update_direction_and_moves(game, key);
}

void	ft_handle_keypress(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
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
