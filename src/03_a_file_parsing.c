/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_a_file_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:14:27 by amarroyo          #+#    #+#             */
/*   Updated: 2025/03/17 17:36:27 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_initialize_grid(char **grid, int max_height)
{
	int	i;

	i = 0;
	while (i < max_height)
	{
		grid[i] = NULL;
		i++;
	}
}

char	**ft_allocate_grid(int max_height)
{
	char	**grid;

	if (max_height <= 0)
	{
		ft_map_error_handling(ERR_MAP_INVALID);
		return (NULL);
	}
	grid = NULL;
	grid = malloc(max_height * sizeof(char *));
	if (!grid)
	{
		ft_system_error_handling(ERR_SYSTEM, NULL);
		return (NULL);
	}
	ft_initialize_grid(grid, max_height);
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
