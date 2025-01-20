/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_a_file_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:14:27 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/20 13:20:17 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_open_map_file(const char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}

void	ft_initialize_grid(char **grid, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		grid[i] = NULL;
		i++;
	}
}

char	**ft_allocate_grid(int size)
{
	char	**grid;

	if (size <= 0)
	{
		ft_map_error_handling(ERR_MAP_INVALID);
		return (NULL);
	}
	grid = malloc(size * sizeof(char *));
	if (!grid)
	{
		ft_system_error_handling(ERR_SYSTEM, NULL);
		return (NULL);
	}
	ft_initialize_grid(grid, size);
	return (grid);
}

void	ft_free_map_grid(char **grid, int line_count)
{
	int	i;

	if (!grid)
		return ;
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
	grid = NULL;
}
