/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_indice_variable.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:52:45 by aguemazi          #+#    #+#             */
/*   Updated: 2022/07/22 09:29:14 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_indice_variable(char *env[], char *variable)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], ft_strjoin(variable, "="), 5 * sizeof(char)) != 0)
	{
		i ++;
	}
	if (!env[i])
		return (-1);
	return (i);
}