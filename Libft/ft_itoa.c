/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:48:02 by aguemazi          #+#    #+#             */
/*   Updated: 2022/03/04 15:00:28 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int nbr)
{
	if (nbr < 0)
		nbr = -nbr;
	return (nbr);
}

static size_t	ft_nbrlen(int n)
{
	size_t	size;

	size = 0;
	while (n / 10 != 0)
	{
		n = n / 10;
		size ++;
	}
	size ++;
	return (size);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		is_neg;
	size_t	size;

	is_neg = (n < 0);
	size = ft_nbrlen(n);
	str = malloc(sizeof(char) * size + 1 + is_neg);
	if (!str)
		return (NULL);
	str[size + is_neg] = '\0';
	size --;
	while (n != 0)
	{
		str[size + is_neg] = '0' + ft_abs(n % 10);
		n = (n / 10);
		size--;
	}
	str[size + is_neg] = '0' + ft_abs(n % 10);
	size--;
	if (is_neg)
		str[0] = '-';
	return (str);
}
