/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:12:47 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/21 13:21:07 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Dinamically allocated window

// Test floor
int	main(int argc, char **argv)
{
	t_map		map;
	t_config	config;
	t_error		error;

	ft_init_config(&config);
	if (argc != 2)
	{
		ft_printf("Usage: ./so_long <map_file.ber>\n");
		return (EXIT_FAILURE);
	}
	error = ft_parse_map(argv[1], &map, &config);
	if (error != ERR_NONE)
	{
		ft_error_handling(error, argv[1]);
		return (EXIT_FAILURE);
	}
	ft_printf("Map validation successful!\n");
	// Calculate the dynamic window size based on map dimensions and TILE_SIZE
    int window_width = map.width * TILE_SIZE;
    int window_height = map.height * TILE_SIZE;

    // Initialize the window with the calculated size
    mlx_t *mlx = mlx_init(window_width, window_height, "so_long", false);
    if (!mlx)
    {
        ft_printf("Failed to initialize MLX42\n");
        ft_free_map_grid(map.grid, map.height);
        return (EXIT_FAILURE);
    }
	// Initialize MLX42
    // mlx_t *mlx = mlx_init(800, 600, "so_long", true);
    // if (!mlx)
    // {
    //     fprintf(stderr, "Failed to initialize MLX42\n");
    //     ft_free_map_grid(map.grid, map.height); // Ensure memory cleanup
    //     return EXIT_FAILURE;
    // }

    // Load the floor tile texture
    mlx_texture_t *floor_texture = mlx_load_png("textures/floor_aff.png");
    if (!floor_texture)
    {
        fprintf(stderr, "Failed to load floor texture\n");
        mlx_terminate(mlx);
        ft_free_map_grid(map.grid, map.height); // Ensure memory cleanup
        return EXIT_FAILURE;
    }

    // Convert the texture to an image
    mlx_image_t *floor_image = mlx_texture_to_image(mlx, floor_texture);
    if (!floor_image)
    {
        fprintf(stderr, "Failed to convert texture to image\n");
        mlx_delete_texture(floor_texture);
        mlx_terminate(mlx);
        ft_free_map_grid(map.grid, map.height); // Ensure memory cleanup
        return EXIT_FAILURE;
    }

    // Render the floor tiles
    render_floor(mlx, floor_image, &map);

    // Free the floor texture as it's no longer needed
    mlx_delete_texture(floor_texture);

    // Start the MLX42 loop
    mlx_loop(mlx);

    // Clean up resources
    mlx_terminate(mlx);
	ft_free_map_grid(map.grid, map.height);
	return (EXIT_SUCCESS);
}


// Main para dibujar grid
// int	main(void)
// {
// 	// Inicializar MLX42
// 	mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "so_long", false);
// 	if (!mlx)
// 	{
// 		fprintf(stderr, "Error inicializando MLX42\n");
// 		return (EXIT_FAILURE);
// 	}

// 	// Crear una imagen del tamaño de la ventana
// 	mlx_image_t *img = mlx_new_image(mlx, WIDTH, HEIGHT);
// 	if (!img)
// 	{
// 		fprintf(stderr, "Error creando imagen\n");
// 		mlx_terminate(mlx);
// 		return (EXIT_FAILURE);
// 	}

// 	// Dibujar fondo verde
// 	int x = 0;
// 	int y = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIDTH)
// 		{
// 			mlx_put_pixel(img, x, y, 0x00FF00FF); // Verde
// 			x++;
// 		}
// 		y++;
// 	}

// 	// Dibujar cuadrícula
// 	draw_grid(img);

// 	// Mostrar la imagen en la ventana
// 	mlx_image_to_window(mlx, img, 0, 0);

// 	// Bucle principal
// 	mlx_loop(mlx);

// 	// Liberar recursos al cerrar
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }

// int	main(void)
// {
// 	mlx_t		*mlx;
// 	mlx_image_t	*img;

// 	// Inicializar MLX42 con dimensiones fijas
// 	mlx = mlx_init(WIDTH, HEIGHT, "so_long", false);
// 	if (!mlx)
// 	{
// 		fprintf(stderr, "Error inicializando MLX42\n");
// 		return (EXIT_FAILURE);
// 	}
// 	// Crear una imagen para dibujar
// 	img = mlx_new_image(mlx, WIDTH, HEIGHT);
// 	if (!img)
// 	{
// 		fprintf(stderr, "Error creando imagen\n");
// 		mlx_terminate(mlx);
// 		return (EXIT_FAILURE);
// 	}
// 	// Rellenar la imagen con un color (marcador de prueba)
// 	for (uint32_t y = 0; y < HEIGHT; ++y)
// 		for (uint32_t x = 0; x < WIDTH; ++x)
// 			mlx_put_pixel(img, x, y, 0x00FF00FF); // Color verde
// 	// Dibujar la imagen en la ventana
// 	mlx_image_to_window(mlx, img, 0, 0);
// 	// Bucle principal
// 	mlx_loop(mlx);
// 	// Liberar recursos al cerrar
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }

// Main to test map parsing and path validation + screen limits

// int	main(int argc, char **argv)
// {
// 	t_map		map;
// 	t_config	config;
// 	t_error		error;

// 	ft_init_config(&config);
// 	if (argc != 2)
// 	{
// 		ft_printf("Usage: ./so_long <map_file.ber>\n");
// 		return (EXIT_FAILURE);
// 	}
// 	error = ft_parse_map(argv[1], &map, &config);
// 	if (error != ERR_NONE)
// 	{
// 		ft_error_handling(error, argv[1]);
// 		return (EXIT_FAILURE);
// 	}
// 	ft_printf("Map validation successful!\n");
// 	ft_free_map_grid(map.grid, map.height);
// 	return (EXIT_SUCCESS);
// }
