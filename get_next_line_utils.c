/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:54:45 by brmaria-          #+#    #+#             */
/*   Updated: 2025/05/22 17:54:50 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *c)
{
	size_t	count;

	if (!c)
		return (0);
	count = 0;
	while (c[count])
		count++;
	return (count);
}

ssize_t	ft_strchr(char *s)
{
	ssize_t	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_memmove(char *buffer)
{
	ssize_t	index;
	ssize_t	nl_index;

	index = 0;
	nl_index = ft_strchr(buffer) + 1;
	while (buffer[index + nl_index] && nl_index)
	{
		buffer[index] = buffer[index + nl_index];
		index++;
	}
	while (index < BUFFER_SIZE)
	{
		buffer[index] = '\0';
		index++;
	}
}

char	*ft_strjoin_free(char *line, char *buffer)
{
	ssize_t	i;
	ssize_t	j;
	char	*nl;

	if (!line)
	{
		line = malloc(1);
		if (!line)
			return (NULL);
		line[0] = '\0';
	}
	nl = malloc((ft_strlen(line) + ft_strlen(buffer) + 1) * sizeof(char));
	if (nl)
	{
		i = -1;
		j = -1;
		while (line[++i])
			nl[i] = line[i];
		while (buffer[++j])
			nl[i + j] = buffer[j];
		nl[i + j] = '\0';
	}
	free (line);
	return (nl);
}
