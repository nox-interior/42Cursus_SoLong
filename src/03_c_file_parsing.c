/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_c_file_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:12:49 by amarroyo          #+#    #+#             */
/*   Updated: 2025/03/24 16:02:29 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_error	ft_validate_line(char *line, t_map *map, uint32_t *line_count)
{
	size_t	line_length;

	if (!line || !map || !map->grid)
	{
		free(line);
		return (ERR_MAP_INVALID);
	}
	line_length = ft_strlen(line);
	if (line_length > 0 && line[line_length - 1] == '\n')
		line_length--;
	if (*line_count == 0)
		map->width = line_length;
	else if (line_length != map->width)
	{
		free(line);
		return (ERR_MAP_INVALID);
	}
	map->grid[*line_count] = ft_strdup(line);
	free(line);
	if (!map->grid[*line_count])
		return (ERR_SYSTEM);
	(*line_count)++;
	return (ERR_NONE);
}

static void	ft_free_on_read_error(char *line, char *store_buffer, t_map *map,
		int line_count)
{
	if (line)
		free(line);
	if (store_buffer)
		free(store_buffer);
	if (map->grid)
	{
		ft_free_map_grid(map->grid, line_count);
		map->grid = NULL;
	}
}

static t_error	ft_finalize_map(t_map *map, int line_count)
{
	if (line_count == 0)
		return (ERR_MAP_INVALID);
	map->grid[line_count] = NULL;
	map->height = line_count;
	return (ERR_NONE);
}

t_error	ft_read_map_lines(int fd, t_map *map, t_winconfig *winconfig)
{
	char		*line;
	char		*store_buffer;
	uint32_t	line_count;

	store_buffer = NULL;
	line_count = 0;
	while (1)
	{
		line = get_next_line(fd, &store_buffer);
		if (!line)
			break ;
		if (line_count >= winconfig->max_map_height)
		{
			ft_free_on_read_error(line, store_buffer, map, line_count);
			return (ERR_SCREEN_LIMIT);
		}
		if (ft_validate_line(line, map, &line_count) != ERR_NONE)
		{
			ft_free_on_read_error(NULL, store_buffer, map, line_count);
			return (ERR_MAP_INVALID);
		}
	}
	free(store_buffer);
	return (ft_finalize_map(map, line_count));
}
