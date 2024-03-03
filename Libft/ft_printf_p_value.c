/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:22:15 by aguemazi          #+#    #+#             */
/*   Updated: 2022/03/25 15:25:33 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_p_value(va_list ptr)
{
	char	*hexalow;
	int		ret;

	ret = 0;
	hexalow = "0123456789abcdef";
	write(1, "0x", 2);
	ft_printf_putnbr_base2(va_arg(ptr, unsigned long int), hexalow, &ret);
	ret += 2;
	return (ret);
}
