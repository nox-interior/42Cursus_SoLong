/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_file_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:14:27 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/13 16:56:09 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_open_map_file(const char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		ft_system_error_handling(ERR_FILE_OPEN, file_path);
	return (fd);
}

static void	ft_initialize_grid(char **grid, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		grid[i] = NULL;
		i++;
	}
}
static char	**ft_allocate_grid(int initial_size)
{
	char	**grid;

	grid = malloc(initial_size * sizeof(char *));
	if (!grid)
	{
		ft_system_error_handling(ERR_SYSTEM, NULL);
		return (NULL);
	}
	ft_initialize_grid(grid, initial_size);
	return (grid);
}

void	ft_free_map_grid(char **grid, int line_count)
{
	int	i;

	i = 0;
	while (i < line_count)
	{
		if (grid[i] != NULL)
		{
			free(grid[i]);
			grid[i] = NULL;
		}
		i++;
	}
	free(grid);
}

t_error	ft_parse_map(const char *file_path, t_map *map)
{
	int		fd;
	t_error	error;

	fd = ft_open_map_file(file_path);
	if (fd == -1)
		return (ERR_FILE_OPEN);
	map->grid = ft_allocate_grid(INITIAL_GRID_SIZE);
	if (!map->grid)
	{
		close(fd);
		return (ERR_SYSTEM);
	}
	error = ft_read_map_lines(fd, map);
	close(fd);
	if (error != ERR_NONE)
	{
		ft_free_map_grid(map->grid, INITIAL_GRID_SIZE);
		return (error);
	}
	if (map->height == 0)
	{
		ft_free_map_grid(map->grid, map->height);
		return (ERR_MAP_INVALID);
	}
	return (ERR_NONE);
}

