/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_c_file_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:12:49 by amarroyo          #+#    #+#             */
/*   Updated: 2025/03/18 16:36:23 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_error	ft_validate_line(char *line, t_map *map, uint32_t line_count)
{
	size_t	line_length;

	if (!line || !map || !map->grid)
		return (ERR_MAP_INVALID);
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

t_error	ft_process_line(char *line, t_map *map, int line_count)
{
	t_error	error;

	error = ft_validate_line(line, map, line_count);
	free(line);
	if (error != ERR_NONE)
		return (error);
	return (ERR_NONE);
}
