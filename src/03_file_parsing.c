/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_file_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:14:27 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/10 12:15:13 by amarroyo         ###   ########.fr       */
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

static char	**ft_allocate_grid(int initial_size)
{
	char	**grid;

	grid = malloc(initial_size * sizeof(char *));
	if (!grid)
		ft_system_error_handling(ERR_SYSTEM, NULL);
	return (grid);
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
	return (error);
}
