/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:17:01 by aguemazi          #+#    #+#             */
/*   Updated: 2022/03/07 10:51:10 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (dst[i])
	{
		i++;
	}
	while (dstsize > 0 && i + j < dstsize - 1 && src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
		dst[i + j] = '\0';
	while (src[j])
	{
		j++;
	}
	if (dstsize < i)
		return (j + dstsize);
	return (i + j);
}
