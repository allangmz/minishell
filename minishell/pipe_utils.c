/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:09:05 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/12/17 20:15:55 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_gestion_quote_count_pipe(char *str, int *i)
{
	if (str[*i] && str[*i] == '\'')
	{
		*i += 1;
		while (str[*i] && str[*i] != '\'')
		{
			*i += 1;
		}
		*i += 1;
	}
	if (str[*i] && str[*i] == '\"')
	{
		*i += 1;
		while (str[*i] && str[*i] != '\"')
		{
			*i += 1;
		}
		*i += 1;
	}
}

int	ft_count_pipe(char *str)
{
	int		pipe_count;
	int		i;

	i = 0;
	pipe_count = 1;
	while (str[i])
	{
		ft_gestion_quote_count_pipe(str, &i);
		if (str[i] && str[i] == '|')
			pipe_count++;
		i++;
	}
	return (pipe_count);
}
