/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_b_file_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:50:54 by amarroyo          #+#    #+#             */
/*   Updated: 2025/03/24 16:53:32 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_error	ft_open_and_allocate(const char *file_path, t_map *map,
		t_winconfig *winconfig, int *fd)
{
	*fd = open(file_path, O_RDONLY);
	if (*fd == -1)
		return (ERR_OPEN_FILE);
	map->grid = ft_allocate_grid(winconfig->max_map_height);
	if (!map->grid)
	{
		close(*fd);
		return (ERR_SYSTEM);
	}
	return (ERR_NONE);
}

static t_error	ft_free_map_error(t_error error, t_map *map, int fd)
{
	if (map->grid != NULL)
	{
		ft_free_map_grid(map->grid, map->height);
		map->grid = NULL;
	}
	close(fd);
	return (error);
}

static t_error	ft_check_no_trailing_newline(const char *file_path)
{
	int		fd;
	char	buffer[1024];
	ssize_t	n;
	char	last;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (ERR_OPEN_FILE);
	last = '\0';
	while (1)
	{
		n = read(fd, buffer, 1024);
		if (n <= 0)
			break ;
		last = buffer[n - 1];
	}
	close(fd);
	if (n < 0)
		return (ERR_READ_FILE);
	if (last == '\n')
		return (ERR_MAP_INVALID);
	return (ERR_NONE);
}

static t_error	ft_finish_parse(t_map *map, t_winconfig *winconfig,
	int fd, t_error error)
{
	close(fd);
	if (error != ERR_NONE)
		return (ft_free_map_error(error, map, fd));
	error = ft_validate_screen_limit(map, winconfig);
	if (error != ERR_NONE)
		return (ft_free_map_error(error, map, fd));
	error = ft_validate_map(map);
	if (error != ERR_NONE)
		return (ft_free_map_error(error, map, fd));
	error = ft_validate_path(map);
	if (error != ERR_NONE)
		return (ft_free_map_error(error, map, fd));
	return (ERR_NONE);
}

t_error	ft_parse_map(const char *file_path, t_map *map, t_winconfig *winconfig)
{
	int		fd;
	t_error	error;

	error = ft_check_extension(file_path);
	if (error != ERR_NONE)
		return (error);
	error = ft_check_no_trailing_newline(file_path);
	if (error != ERR_NONE)
		return (error);
	ft_init_map(map);
	error = ft_open_and_allocate(file_path, map, winconfig, &fd);
	if (error != ERR_NONE)
		return (error);
	error = ft_read_map_lines(fd, map, winconfig);
	if (error != ERR_NONE)
		return (ft_free_map_error(error, map, fd));
	return (ft_finish_parse(map, winconfig, fd, error));
}
