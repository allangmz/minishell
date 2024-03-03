/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:32:43 by aguemazi          #+#    #+#             */
/*   Updated: 2022/04/09 14:30:18 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printf_value(va_list ptr, const char *str, int i)
{
	int		ret;

	ret = 0;
	if (str[i] == 'c')
		ret = ft_printf_c_value(ptr);
	if (str[i] == 's')
		ret = ft_printf_s_value(ptr);
	if (str[i] == 'p')
		ret += ft_printf_p_value(ptr);
	if (str[i] == 'd' || str[i] == 'i')
		ret = ft_printf_d_or_i_value(va_arg(ptr, int));
	if (str[i] == 'u')
		ft_printf_putuns_fd(va_arg(ptr, int), 1, &ret);
	if (str[i] == 'x')
		ft_printf_putnbr_base(va_arg(ptr, int), "0123456789abcdef", &ret);
	if (str[i] == 'X')
		ft_printf_putnbr_base(va_arg(ptr, int), "0123456789ABCDEF", &ret);
	if (str [i] == '%')
		ret += ft_printf_percent_value();
	return (ret);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		ret;
	va_list	ptr;

	va_start(ptr, str);
	i = 0;
	ret = 0;
	while (str[i])
	{	
		if (str[i] && str[i] == '%')
		{
			i++;
			ret += ft_printf_value(ptr, str, i);
			i++;
		}
		while (str[i] && str[i] != '%')
		{
			write(1, &str[i], 1);
			ret++;
			i++;
		}
	}
	va_end(ptr);
	return (ret);
}
