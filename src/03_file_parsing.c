/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_file_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:14:27 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/10 11:53:19 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define INITIAL_GRID_SIZE 100

int	ft_open_map_file(const char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		ft_system_error_handling(ERR_FILE_OPEN, file_path);
	return (fd);
}

static char	**ft_allocate_grid(int initial_size)
{
	char	**grid;

	grid = malloc(initial_size * sizeof(char *));
	if (!grid)
		ft_system_error_handling(ERR_SYSTEM, NULL);
	return (grid);
}

static char	**ft_resize_grid(char **old_grid, int old_size, int new_size)
{
	char	**new_grid;
	int		i;

	new_grid = malloc(new_size * sizeof(char *));
	if (!new_grid)
	{
		ft_system_error_handling(ERR_SYSTEM, NULL);
		return (NULL);
	}
	i = 0;
	while (i < old_size)
	{
		new_grid[i] = old_grid[i];
		i++;
	}
	free(old_grid);
	return (new_grid);
}

static t_error	ft_validate_line_length(char *line, int expected_width)
{
	if ((int)ft_strlen(line) != expected_width)
	{
		free(line);
		return (ERR_MAP_INVALID);
	}
	return (ERR_NONE);
}

t_error	ft_read_map_lines(int fd, t_map *map)
{
	char	*line;
	int		line_count;
	int		alloc_lines;

	line_count = 0;
	alloc_lines = INITIAL_GRID_SIZE;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line_count >= alloc_lines)
		{
			map->grid = ft_resize_grid(map->grid, alloc_lines, alloc_lines * 2);
			if (!map->grid)
				return (ERR_SYSTEM);
			alloc_lines *= 2;
		}
		if (line_count == 0)
			map->width = ft_strlen(line);
		else if (ft_validate_line_length(line, map->width) != ERR_NONE)
			return (ERR_MAP_INVALID);
		map->grid[line_count++] = line;
	}
	map->height = line_count;
	return (ERR_NONE);
}
