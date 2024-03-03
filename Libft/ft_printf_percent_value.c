/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_percent_value.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:23:37 by aguemazi          #+#    #+#             */
/*   Updated: 2022/03/25 15:39:26 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_percent_value(void)
{
	int	ret;

	ret = 0;
	write(1, "%", 1);
	ret ++;
	return (ret);
}
