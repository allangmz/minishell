/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_indice_variable.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:52:45 by aguemazi          #+#    #+#             */
/*   Updated: 2022/08/17 14:12:11 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_indice_variable(char *env[], char *variable)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strjoin(variable, "=");
	while (env[i] && ft_strncmp(env[i], str, 5 * sizeof(char)) != 0)
	{
		i ++;
	}
	free(str);
	if (!env[i])
		return (-1);
	return (i);
}