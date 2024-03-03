/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:21:48 by aguemazi          #+#    #+#             */
/*   Updated: 2022/03/25 15:26:27 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_s_value(va_list ptr)
{
	char	*string;
	int		ret;

	ret = 0;
	string = va_arg(ptr, char *);
	if (!string)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ret = ft_strlen(string);
	ft_putstr_fd(string, 1);
	return (ret);
}
