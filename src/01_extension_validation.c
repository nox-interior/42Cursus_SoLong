/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_extension_validation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 08:46:56 by amarroyo          #+#    #+#             */
/*   Updated: 2025/03/17 13:15:06 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_error	ft_check_extension(const char *str)
{
	int	i;

	i = 0;
	if (! str || ft_strlen(str) < 4)
		return (ERR_FILE_PATH_INVALID);
	while (str[i] != '\0')
		i++;
	i--;
	if (str[i] != 'r' || str[i - 1] != 'e' || str[i - 2] != 'b'
		|| str[i - 3] != '.')
		return (ERR_EXTENSION_INVALID);
	return (ERR_NONE);
}

// t_error	ft_check_extension(const char *str)
// {
// 	int	len;

// 	if (!str || ft_strlen(str) < 5)
// 		return (ERR_FILE_PATH_INVALID);
// 	len = ft_strlen(str);
// 	if (str[len - 4] == '.' && str[len - 5] == '/')
// 		return (ERR_FILE_PATH_INVALID);
// 	if (str[len - 1] != 'r' || str[len - 2] != 'e' || str[len - 3] != 'b'
// 		|| str[len - 4] != '.')
// 		return (ERR_EXTENSION_INVALID);
// 	return (ERR_NONE);
// }
