/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:12:47 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/20 10:30:22 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "so_long.h"  // Ensure your header includes necessary declarations

int main(int argc, char **argv)
{
    t_map   map;
    t_error error;

    // Initial debug to verify constant values
    printf("Runtime Debug MAIN: TILE_SIZE=%d, MAX_MAP_H=%d, MAX_MAP_W=%d\n",
           TILE_SIZE, MAX_MAP_H, MAX_MAP_W);

    if (argc != 2)
    {
        ft_printf("Usage: ./so_long <map_file.ber>\n");
        return (EXIT_FAILURE);
    }

    // Debug: Start parsing
    printf("Debug MAIN00: Parsing map...\n");

    // Parse and validate the map
    error = ft_parse_map(argv[1], &map);

    // Check if map parsing was successful
    if (error != ERR_NONE)
    {
        ft_error_handling(error, argv[1]);
        return (EXIT_FAILURE);
    }

    // Post-parse debug information
    printf("Post ft_parse_map: MAX_MAP_H=%d, MAX_MAP_W=%d\n", MAX_MAP_H, MAX_MAP_W);
    ft_printf("Map validation successful!\n");

    // Free allocated map resources
    ft_free_map_grid(map.grid, map.height);

    return (EXIT_SUCCESS);
}

// int main(int argc, char **argv)
// {
//     t_map   map;
//     t_error error;

//     // Initial debug for global variables
//     printf("Runtime Debug MAIN: TILE_SIZE=%d, MAX_MAP_H=%d (address=%p), MAX_MAP_W=%d (address=%p)\n",
//            TILE_SIZE, MAX_MAP_H, (void *)&MAX_MAP_H, MAX_MAP_W, (void *)&MAX_MAP_W);

//     if (argc != 2)
//     {
//         ft_printf("Usage: ./so_long <map_file.ber>\n");
//         return (EXIT_FAILURE);
//     }

//     // Split the problematic debug statement into smaller, focused parts
//     ft_printf("Debug MAIN00 (Width): MAX_MAP_W=%d\n", MAX_MAP_W);
//     ft_printf("Debug MAIN00 (Height): MAX_MAP_H=%d\n", MAX_MAP_H);
//     ft_printf("Debug MAIN00 Addresses: MAX_MAP_W=%p, MAX_MAP_H=%p\n",
//               (void *)&MAX_MAP_W, (void *)&MAX_MAP_H);

//     // Parse and validate the map
//     printf("Debug MAIN00: Parsing map...\n");
//     error = ft_parse_map(argv[1], &map);

//     // Check if map parsing was successful
//     if (error != ERR_NONE)
//     {
//         ft_error_handling(error, argv[1]);
//         return (EXIT_FAILURE);
//     }

//     // Post-parse debug information
//     printf("Post ft_parse_map: MAX_MAP_H=%d (address=%p), MAX_MAP_W=%d (address=%p)\n",
//            MAX_MAP_H, (void *)&MAX_MAP_H, MAX_MAP_W, (void *)&MAX_MAP_W);

//     ft_printf("Map validation successful!\n");

//     // Free allocated resources for the map grid
//     ft_free_map_grid(map.grid, map.height);

//     return (EXIT_SUCCESS);
// }
