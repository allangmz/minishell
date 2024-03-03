/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:35:39 by aguemazi          #+#    #+#             */
/*   Updated: 2022/07/06 10:33:17 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		nbr;
	int		negative;
	char	*str2;

	nbr = 0;
	negative = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' && negative++ == 0)
		str++;
	else if (*str == '+')
		str++;
	str2 = (char *)str;
	while (*str2 >= '0' && *str2 <= '9')
		str2++;
	if ((str2 - str) > 10 && negative == 0)
		return (-1);
	else if ((str2 - str) > 10 && negative == 1)
		return (0);
	while ((*str >= '0' && *str <= '9'))
		nbr = nbr * 10 + *str++ - 48;
	if (negative != 0)
		nbr -= (nbr * 2);
	return (nbr);
}
