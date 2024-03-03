/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:01:32 by aguemazi          #+#    #+#             */
/*   Updated: 2022/05/06 11:29:21 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_next_line_line(char *line, char *buffer, int octet, int fd)
{
	while (buffer[0] != '\n' && octet > 0)
	{
		octet = read(fd, buffer, 1);
		buffer[octet] = '\0';
		line = ft_strjoin(line, buffer);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		buffer[2];
	char		*line;
	int			octet;
	int static	stat = BUFFER_SIZE;

	line = NULL;
	octet = 0;
	if (octet == 0)
	{
		octet = read(fd, buffer, 1);
		buffer[octet] = '\0';
		line = ft_strjoin(line, buffer);
	}
	if (octet > 0 && buffer[0] != '\0')
		line = ft_get_next_line_line(line, buffer, octet, fd);
	else
	{
		free(line);
		return (NULL);
	}
	stat--;
	return (line);
}
