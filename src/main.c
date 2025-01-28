/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:13:08 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/28 14:49:05 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(int argc, char **argv)
{
    t_map map;
    t_game game;
    t_config config;
    t_error error;

    if (argc != 2)
    {
        ft_putstr_fd("Usage: ./so_long <map_file.ber>\n", 1);
        return (EXIT_FAILURE);
    }
    ft_init_config(&config);
    ft_init_game(&game, &map);
    game.map = malloc(sizeof(t_map));
    if (!game.map)
    {
        ft_printf("Error: Failed to allocate memory for map.\n");
        return (EXIT_FAILURE);
    }
    error = ft_parse_map(argv[1], game.map, &config);
    if (error != ERR_NONE)
    {
        ft_error_handling(error, argv[1]);
        free(game.map);
        return (EXIT_FAILURE);
    }
    int window_width = game.map->width * TILE_SIZE;
    int window_height = game.map->height * TILE_SIZE;
    game.mlx = mlx_init(window_width, window_height, "so_long", false);
    if (!game.mlx)
    {
        ft_printf("Failed to initialize MLX42\n");
        ft_free_map_grid(game.map->grid, game.map->height);
        free(game.map);
        return (EXIT_FAILURE);
    }

    // Load textures
    ft_init_textures(&game);

    // Render the initial map and player
    ft_render_map(&game);
    ft_render_player(&game);

    // Set up keypress handling and start the MLX42 loop
    mlx_key_hook(game.mlx, ft_handle_keypress, &game);
    mlx_loop(game.mlx);
	mlx_terminate(game.mlx);

    // Clean up resources after exiting
    ft_exit_game(&game);
    return (EXIT_SUCCESS);
}
// int	main(int argc, char **argv)
// {
// 	t_map	map;
// 	t_game	game;
// 	t_config config;
// 	t_error	error;

// 	if (argc != 2)
// 	{
// 		ft_putstr_fd("Usage: ./so_long <map_file.ber>\n", 1);
// 		return (EXIT_FAILURE);
// 	}
// 	ft_init_config(&config);
// 	ft_init_game(&game, &map);
// 	game.map = malloc(sizeof(t_map));
// 	if (!game.map)
// 	{
// 		ft_printf("Error: Failed to allocate memory for map.\n");
// 		return (EXIT_FAILURE);
// 	}
// 	error = ft_parse_map(argv[1], game.map, &config);
// 	if (error != ERR_NONE)
// 	{
// 		ft_error_handling(error, argv[1]);
// 		free(game.map); //delete?
// 		return (EXIT_FAILURE);
// 	}
// 	int window_width = game.map->width * TILE_SIZE;
// 	int window_height = game.map->height * TILE_SIZE;
// 	game.mlx = mlx_init(window_width, window_height, "so_long", false);
// 	if (!game.mlx)
// 	{
// 		ft_printf("Failed to initialize MLX42\n");
// 		ft_free_map_grid(game.map->grid, game.map->height);
// 		free(game.map); //delete?
// 		return (EXIT_FAILURE);
// 	}

// 	// Load textures
// 	ft_init_textures(&game);

// 	// Render the initial map and player
// 	ft_render_map(&game);
// 	ft_render_player(&game);

// 	// Set up keypress handling and start the MLX42 loop
// 	mlx_key_hook(game.mlx, ft_handle_keypress, &game);
// 	mlx_loop(game.mlx);

// 	// Clean up resources after exiting
// 	ft_free_map_grid(game.map->grid, game.map->height);
// 	ft_exit_game(&game);
// 	mlx_terminate(game.mlx); //delete?
// 	free(game.map); //delete?
// 	return (EXIT_SUCCESS);
// }
