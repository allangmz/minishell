/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr_base.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:31:53 by aguemazi          #+#    #+#             */
/*   Updated: 2022/03/25 15:33:48 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printf_putnbr_base(unsigned int nbr, const char *base, int *i)
{
	unsigned int	size;

	size = ft_strlen(base);
	if (nbr >= size)
	{
		ft_printf_putnbr_base(nbr / size, base, i);
		ft_putchar_fd(base[nbr % size], 1);
	}
	else
	{
		ft_putchar_fd(base[nbr % size], 1);
	}
	*i = *i + 1;
}
