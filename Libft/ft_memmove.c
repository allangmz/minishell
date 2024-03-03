/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 09:59:59 by aguemazi          #+#    #+#             */
/*   Updated: 2022/03/04 14:58:48 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*destination;
	unsigned char	*source;

	if (!dst && !src)
		return (0);
	destination = (unsigned char *) dst;
	source = (unsigned char *) src;
	if (destination < source)
	{
		ft_memcpy(destination, source, len);
		return ((void *) destination);
	}
	while (len > 0)
	{
		destination[len - 1] = source [len - 1];
		len --;
	}
	return ((void *) destination);
}
