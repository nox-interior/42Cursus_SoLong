/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:12:47 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/20 18:06:51 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	ft_free_map_grid(map.grid, map.height);
	return (EXIT_SUCCESS);
}
