/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:32:22 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/12 11:14:26 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void	ft_echo(char	**str_split)
{
	int	new_line_at_end;
	int	i;

	new_line_at_end = 1;
	i = 1;
	if (str_split[1] && ft_strcmp(str_split[1], "-n") == 0)
	{
		new_line_at_end = 0;
		i = 2;
	}
	while (str_split[i])
	{
		ft_putstr_fd(str_split[i], STDOUT_FILENO);
		i++;
	}
	if (new_line_at_end)
	{
		ft_putchar_fd('\n', 1);
	}
	return ;
}
