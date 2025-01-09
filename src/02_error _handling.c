/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_error _handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:15:13 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/09 16:22:14 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_handle_error(t_error error_code, const char *context)
{
	if (error_code == ERR_INVALID_EXTENSION)
		ft_printf("Error: The file extension is not valid.\n");
	else if (error_code == ERR_FILE_NOT_FOUND)
		ft_printf("Error: File not found: %s\n", context);
	else if (error_code == ERR_NO_VALID_MAP)
		ft_printf("Error: Invalid map format in file: %s\n", context);
	// Handle more error cases here
	else
		ft_printf("An unknown error occurred.\n");
}
