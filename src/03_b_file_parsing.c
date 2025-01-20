/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_b_file_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:50:54 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/20 10:27:59 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_error	ft_open_and_allocate(const char *file_path, t_map *map, int *fd)
{
	*fd = ft_open_map_file(file_path);
	if (*fd == -1)
		return (ERR_OPEN_FILE);
	printf("Debug (03_b_file_parsing): MAX_MAP_H=%d before calling ft_allocate_grid\n", MAX_MAP_H);
	printf("Debug (ft_open_and_allocate): Allocating grid with MAX_MAP_H=%d\n", MAX_MAP_H);
	map->grid = ft_allocate_grid(MAX_MAP_H);
	printf("Debug (03_b_file_parsing): ft_allocate_grid called successfully, map->grid=%p\n", (void *)map->grid);
	printf("Debug (ft_open_and_allocate): Allocating grid with MAX_MAP_H=%d\n", MAX_MAP_H);
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
		ft_free_map_grid(map->grid, INITIAL_GRID_SIZE);
		map->grid = NULL;
	}
	close(fd);
	return (error);
}

t_error	ft_parse_map(const char *file_path, t_map *map)
{
	int		fd;
	t_error	error;

	error = ft_check_extension(file_path);
	if (error != ERR_NONE)
		return (error);
	ft_init_map(map);
	printf("Debug (ft_parse_map): MAX_MAP_H=%d, MAX_MAP_W=%d before ft_open_and_allocate\n", MAX_MAP_H, MAX_MAP_W);
	error = ft_open_and_allocate(file_path, map, &fd);
	if (error != ERR_NONE)
		return (error);
	printf("Debug (ft_parse_map): After ft_open_and_allocate, map->grid=%p\n", (void *)map->grid);
	printf("Debug (ft_parse_map): Calling ft_read_map_lines\n");
	error = ft_read_map_lines(fd, map);
	printf("Debug (ft_parse_map): After ft_read_map_lines, map->height=%d, map->width=%d\n", map->height, map->width);
	close(fd);
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
