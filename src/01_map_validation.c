/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_map_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 08:46:56 by amarroyo          #+#    #+#             */
/*   Updated: 2025/01/09 15:59:11 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// File handling
int	ft_check_extension(const char *str)
{
	int		i;

	i = 0;
	if (! str || ft_strlen(str) < 5)
	{
		ft_printf("Error: The file extension is not valid.\n");
		return (0);
	}
	while (str[i] != '\0')
		i++;
	i--;
	if (str[i] != 'r' || str[i - 1] != 'e' || str[i - 2] != 'b'
		|| str[i - 3] != '.')
	{
		ft_printf("Error: The file extension is not valid.\n");
		return (0);
	}
	return (1);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        ft_printf("Usage: ./check_extension <file_path>\n");
        return (1);
    }

    if (ft_check_extension(argv[1]))
        ft_printf("File extension is valid.\n");
    else
        ft_printf("File extension is invalid.\n");

    return (0);
}