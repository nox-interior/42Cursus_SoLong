/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarroyo <amarroyo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:57:53 by amarroyo          #+#    #+#             */
/*   Updated: 2025/03/18 12:39:03 by amarroyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"
#include "../../inc/libft.h"

char	*ft_read_file(int fd, char *store_buffer)
{
	char	*buf;
	ssize_t	bytes_read;

	bytes_read = 1;
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	while (ft_strchr(store_buffer, '\n') == NULL && bytes_read != 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buf), free(store_buffer), NULL);
		buf[bytes_read] = '\0';
		store_buffer = ft_join_and_free(store_buffer, buf);
		if (!store_buffer)
			return (free(buf), NULL);
	}
	free(buf);
	return (store_buffer);
}

char	*ft_extract_line(char *store_buffer)
{
	char	*line;
	size_t	i;

	if (!store_buffer || store_buffer[0] == '\0')
		return (NULL);
	i = 0;
	while (store_buffer[i] && store_buffer[i] != '\n')
		i++;
	if (store_buffer[i] == '\n')
		i++;
	line = ft_substr_gnl(store_buffer, 0, i);
	return (line);
}

char	*ft_trim_buffer(char *store_buffer)
{
	char	*new_buffer;
	size_t	i;
	size_t	j;

	if (!store_buffer)
		return (NULL);
	i = 0;
	while (store_buffer[i] && store_buffer[i] != '\n')
		i++;
	if (store_buffer[i] == '\0')
	{
		free(store_buffer);
		return (ft_strdup(""));
	}
	i++;
	new_buffer = ft_calloc(ft_strlen(store_buffer) - i + 1, sizeof(char));
	if (!new_buffer)
		return (NULL);
	j = 0;
	while (store_buffer[i])
		new_buffer[j++] = store_buffer[i++];
	new_buffer[j] = '\0';
	free(store_buffer);
	return (new_buffer);
}

char	*get_next_line(int fd, char **store_buffer)
{
	char	*current_line;
	char	*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || !store_buffer)
		return (NULL);
	*store_buffer = ft_read_file(fd, *store_buffer);
	if (!*store_buffer)
		return (NULL);
	current_line = ft_extract_line(*store_buffer);
	if (!current_line)
	{
		if ((*store_buffer)[0] != '\0')
		{
			current_line = ft_strdup(*store_buffer);
			free(*store_buffer);
			*store_buffer = NULL;
			return (current_line);
		}
		return (NULL);
	}
	tmp = ft_trim_buffer(*store_buffer);
	*store_buffer = tmp;
	return (current_line);
}
