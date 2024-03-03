/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:32:22 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/17 20:54:23 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char **str_split)
{
	int	new_line_at_end;
	int	i;

	new_line_at_end = 1;
	i = 1;
	while (str_split[i] && ft_strcmp(str_split[i], "-n") == 0)
	{
		new_line_at_end = 0;
		i++;
	}
	while (str_split[i])
	{
		ft_putstr_fd(str_split[i], STDOUT_FILENO);
		if (str_split[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (new_line_at_end)
	{
		ft_putchar_fd('\n', 1);
	}
	return ;
}
