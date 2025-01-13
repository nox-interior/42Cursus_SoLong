/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_grid_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:12:49 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/13 16:52:51 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_error	ft_validate_line(char *line, t_map *map, int line_count)
{
	size_t	line_length;

	line_length = ft_strlen(line);
	if (line_length > 0 && line[line_length - 1] == '\n')
		line_length--;
	if (line_count == 0)
		map->width = line_length;
	else if (line_length != map->width)
		return (ERR_MAP_INVALID);
	map->grid[line_count] = ft_strdup(line);
	if (!map->grid[line_count])
		return (ERR_SYSTEM);
	return (ERR_NONE);
}

static void	ft_cleanup_on_error(char *line, char *store_buffer, t_map *map,
		int line_count)
{
	free(line);
	free(store_buffer);
	ft_free_map_grid(map->grid, line_count);
}

t_error	ft_read_map_lines(int fd, t_map *map)
{
	char	*line;
	char	*store_buffer;
	int		line_count;
	t_error	error;

	store_buffer = NULL;
	line_count = 0;
	while ((line = get_next_line(fd, &store_buffer)) != NULL)
	{
		error = ft_validate_line(line, map, line_count);
		free(line);
		if (error != ERR_NONE)
		{
			ft_cleanup_on_error(NULL, store_buffer, map, line_count);
			return (error);
		}
		line_count++;
	}
	free(store_buffer);
	map->grid[line_count] = NULL;
	map->height = line_count;
	if (line_count == 0)
		return (ERR_MAP_INVALID);
	return (ERR_NONE);
}
