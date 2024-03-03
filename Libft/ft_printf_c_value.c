/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:23:14 by aguemazi          #+#    #+#             */
/*   Updated: 2022/03/25 15:24:27 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_c_value(va_list ptr)
{
	int	ret;

	ret = 0;
	ft_putchar_fd(va_arg(ptr, int), 1);
	ret ++;
	return (ret);
}
