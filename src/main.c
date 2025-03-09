/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:13:08 by amarroyo          #+#    #+#             */
/*   Updated: 2025/03/09 16:29:28 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_initialize_game(t_game *game, t_map *map, t_config *config,
		char *map_path)
{
	t_error	error;

	ft_init_config(config);
	ft_init_game(game, map);
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return (EXIT_FAILURE);
	error = ft_parse_map(map_path, game->map, config);
	if (error != ERR_NONE)
	{
		ft_error_handling(error, map_path);
		free(game->map);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_initialize_mlx(t_game *game)
{
	int	window_width;
	int	window_height;

	window_width = game->map->width * TILE_SIZE;
	window_height = game->map->height * TILE_SIZE;
	game->mlx = mlx_init(window_width, window_height, "so_long", false);
	if (!game->mlx)
	{
		ft_free_map_grid(game->map->grid, game->map->height);
		free(game->map);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	ft_start_game_loop(t_game *game)
{
	ft_init_textures(game);
	ft_render_map(game);
	ft_render_player(game);
	mlx_key_hook(game->mlx, ft_handle_keypress, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_map		map;
	t_config	config;

	if (argc != 2)
		return (ft_putstr_fd("Usage: ./so_long <map_file.ber>\n", 1),
			EXIT_FAILURE);
	if (ft_initialize_game(&game, &map, &config, argv[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_initialize_mlx(&game) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_start_game_loop(&game);
	mlx_terminate(game.mlx);
	ft_exit_game(&game);
	return (EXIT_SUCCESS);
}
