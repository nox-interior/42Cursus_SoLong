/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_d_file_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:25:09 by amarroyo          #+#    #+#             */
/*   Updated: 2025/03/18 12:52:56 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_cleanup_on_error(char *line, char *store_buffer, t_map *map,
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

static t_error	ft_handle_map_line(char *line, t_map *map, int *line_count)
{
	t_error	error;

	error = ft_process_line(line, map, *line_count);
	if (error == ERR_NONE)
		(*line_count)++;
	return (error);
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
	char	*line;
	char	*store_buffer;
	int		line_count;

	store_buffer = NULL;
	line_count = 0;
	while (1)
	{
		line = get_next_line(fd, &store_buffer);
		if (!line)
			break ;
		if (line_count >= (int)winconfig->max_map_height)
		{
			ft_cleanup_on_error(line, store_buffer, map, line_count);
			return (ERR_SCREEN_LIMIT);
		}
		if (ft_handle_map_line(line, map, &line_count) != ERR_NONE)
		{
			ft_cleanup_on_error(NULL, store_buffer, map, line_count);
			return (ERR_MAP_INVALID);
		}
	}
	free(store_buffer);
	return (ft_finalize_map(map, line_count));
}
