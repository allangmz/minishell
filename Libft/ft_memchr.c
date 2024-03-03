/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:38:28 by aguemazi          #+#    #+#             */
/*   Updated: 2022/03/04 15:00:46 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*string;
	unsigned char	search;

	string = (unsigned char *) s;
	search = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (string[i] == search)
			return ((void *) &string[i]);
		i++;
	}
	return (0);
}
