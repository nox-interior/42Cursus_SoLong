/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_error_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:27:09 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/15 15:34:25 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_system_error_handling(t_error error_code, const char *ctxt)
{
	if (ctxt)
	{
		if (error_code == ERR_OPEN_FILE)
			ft_printf("Error opening file '%s': %s\n", ctxt, strerror(errno));
		else if (error_code == ERR_READ_FILE)
			ft_printf("Error reading file '%s': %s\n", ctxt, strerror(errno));
		else if (error_code == ERR_SYSTEM)
			ft_printf("System erros '%s': %s\n", ctxt, strerror(errno));
	}
	else
	{
		if (error_code == ERR_OPEN_FILE)
			perror("Error opening file");
		else if (error_code == ERR_READ_FILE)
			perror("Error reading file");
		else if (error_code == ERR_SYSTEM)
			perror("System error");
	}
}

void	ft_map_error_handling(t_error error_code)
{
	if (error_code == ERR_FILE_PATH_INVALID)
		ft_printf("Error: The file path is invalid or too short.\n");
	else if (error_code == ERR_EXTENSION_INVALID)
		ft_printf("Error: The file extension is not '.ber'.\n");
	else if (error_code == ERR_MAP_INVALID)
		ft_printf("Error: The map is empty or invalid.\n");
	else if (error_code == ERR_PLAYER)
		ft_printf("Error: Invalid 'P' count (must be 1).\n");
	else if (error_code == ERR_EXIT)
		ft_printf("Error: Invalid 'E' count (must be 1).\n");
	else if (error_code == ERR_MISSING_COLLECTIBLES)
		ft_printf("Error: Missing collectibles ('C') in the map.\n");
	else
		ft_printf("An unknown error occurred.\n");
}

void	ft_error_handling(t_error error_code, const char *ctxt)
{
	if (error_code == ERR_OPEN_FILE || error_code == ERR_READ_FILE
		|| error_code == ERR_SYSTEM)
		ft_system_error_handling(error_code, ctxt);
	else
		ft_map_error_handling(error_code);
}
