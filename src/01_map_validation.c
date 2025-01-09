/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_map_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 08:46:56 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/09 16:48:16 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// File handling
t_error	ft_check_extension(const char *str)
{
	int		i;

	i = 0;
	if (! str || ft_strlen(str) < 5)
		return (ERR_INVALID_FILE_PATH);
	while (str[i] != '\0')
		i++;
	i--;
	if (str[i] != 'r' || str[i - 1] != 'e' || str[i - 2] != 'b'
		|| str[i - 3] != '.')
		return (ERR_INVALID_EXTENSION);
	return (ERR_NONE);
}

int main(int argc, char **argv)
{
	t_error error;

	if (argc != 2)
	{
		ft_printf("Usage: ./check_extension <file_path>\n");
		return (1);
	}
	error = ft_check_extension(argv[1]);
	if (error != ERR_NONE)
	{
		ft_handle_error(error, argv[1]);
		return (1);
	}
	ft_printf("File extension is valid.\n");
	return (0);
}