/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_b_file_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:50:54 by amarroyo          #+#    #+#             */
/*   Updated: 2025/03/14 10:17:13 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_error	ft_open_and_allocate(const char *file_path, t_map *map,
		t_winconfig *winconfig, int *fd)
{
	t_error	error;
	
	error = ft_open_map_file(file_path, fd);
	if (error != ERR_NONE)
		return (error);
	map->grid = ft_allocate_grid(winconfig->max_map_height);
	if (!map->grid)
	{
		close(*fd);
		return (ERR_SYSTEM);
	}
	return (ERR_NONE);
}

static t_error	ft_handle_map_error(t_error error, t_map *map, int fd)
{
	if (map->grid != NULL)
	{
		ft_free_map_grid(map->grid, map->height);
		map->grid = NULL;
	}
	close(fd);
	return (error);
}

t_error	ft_parse_map(const char *file_path, t_map *map, t_winconfig *winconfig)
{
	int		fd;
	t_error	error;

	error = ft_check_extension(file_path);
	if (error != ERR_NONE)
		return (error);
	ft_init_map(map);
	error = ft_open_and_allocate(file_path, map, winconfig, &fd);
	if (error != ERR_NONE)
		return (error);
	error = ft_read_map_lines(fd, map, winconfig);
	close(fd);
	if (error != ERR_NONE)
		return (ft_handle_map_error(error, map, fd));
	error = ft_validate_screen_limit(map, winconfig);
	if (error != ERR_NONE)
		return (ft_handle_map_error(error, map, fd));
	error = ft_validate_map(map);
	if (error != ERR_NONE)
		return (ft_handle_map_error(error, map, fd));
	error = ft_validate_path(map);
	if (error != ERR_NONE)
		return (ft_handle_map_error(error, map, fd));
	return (ERR_NONE);
}
