#include "so_long.h"
#include <stdio.h>

// Main to check file extension

// int	main(int argc, char **argv)
// {
// 	t_error	error;

// 	if (argc != 2)
// 	{
// 		ft_printf("Usage: ./check_extension <file_path>\n");
// 		return (1);
// 	}
// 	error = ft_check_extension(argv[1]);
// 	if (error != ERR_NONE)
// 	{
// 		ft_error_handling(error, argv[1]);
// 		return (1);
// 	}
// 	ft_printf("File extension is valid.\n");
// 	return (0);
// }


// Main to check file extension + map rectangularity
// #include "so_long.h"

// int	main(int argc, char **argv)
// {
// 	t_map	map;
// 	t_error	error;

// 	// Check argument count
// 	if (argc != 2)
// 	{
// 		ft_printf("Usage: ./so_long <map_file.ber>\n");
// 		return (1);
// 	}

// 	// Validate file extension
// 	if (ft_check_extension(argv[1]) != ERR_NONE)
// 	{
// 		ft_printf("Error: Invalid file extension. Must be '.ber'.\n");
// 		return (1);
// 	}

// 	// Initialize the map structure
// 	map.grid = NULL;
// 	map.width = 0;
// 	map.height = 0;

// 	// Parse the map file and check for errors
// 	error = ft_parse_map(argv[1], &map);
// 	if (error != ERR_NONE)
// 	{
// 		ft_error_handling(error, argv[1]);
// 		return (1);
// 	}

// 	// Print success and map info
// 	ft_printf("Map loaded successfully!\n");
// 	ft_printf("Map dimensions: %d x %d\n", map.width, map.height);

// 	// Print the grid
// 	//ft_print_grid(map.grid, map.height);
// 	ft_printf("Debug: Skipping ft_print_grid for isolation (MAIN).\n");

// 	// Clean up allocated memory
// 	ft_printf("Final map height: %d, width: %d\n", map.height, map.width); //Debug
// 	for (uint32_t i = 0; i < map.height; i++)
// 	{
// 		ft_printf("Debug: Freeing row %d: %s\n", i, map.grid[i]); // Debug print
// 		free(map.grid[i]);
// 	}
// 	free(map.grid);

// 	return (0);
// }

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_map	map;
	t_error	error;

	// Check for proper usage
	if (argc != 2)
	{
		ft_printf("Usage: ./so_long <map_file.ber>\n");
		return (1);
	}

	// Validate file extension
	error = ft_check_extension(argv[1]);
	if (error != ERR_NONE)
	{
		ft_map_error_handling(error);
		return (1);
	}

	// Initialise map structure
	map.grid = NULL;
	map.width = 0;
	map.height = 0;

	// Parse the map file
	error = ft_parse_map(argv[1], &map);
	if (error != ERR_NONE)
	{
		ft_error_handling(error, argv[1]);
		return (1);
	}

	// Display success and map information
	ft_printf("Map loaded successfully!\n");
	ft_printf("Map dimensions: %d x %d\n", map.width, map.height);

	for (uint32_t i = 0; i < map.height; i++)
		ft_printf("%s", map.grid[i]);

	// Free allocated resources
	ft_free_map_grid(map.grid, map.height);
	return (0);
}

// Main to check GNL
// int main(int argc, char **argv)
// {
//     int fd;
//     char *line;

//     // Check for proper usage
//     if (argc != 2)
//     {
//         printf("Usage: %s <file_path>\n", argv[0]);
//         return (1);
//     }

//     // Open the file
//     fd = open(argv[1], O_RDONLY);
//     if (fd == -1)
//     {
//         perror("Error opening file");
//         return (1);
//     }

//     // Read and print lines using get_next_line
//     printf("Reading file: %s\n", argv[1]);
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("Read line: %s", line); // Note: Lines include the newline character
//         free(line); // Always free the line after use
//     }

//     // Close the file
//     close(fd);

//     printf("File reading complete.\n");
//     return (0);
// }