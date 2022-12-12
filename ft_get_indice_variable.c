/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_indice_variable.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:52:45 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/12 12:08:24 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_indice_variable(char *env[], char *variable)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strjoin(variable, "=");
	while (env[i] && ft_strncmp(env[i], str, ft_strlen(str)) != 0)
	{
		i ++;
	}
	free(str);
	if (!env[i])
		return (-1);
	return (i);
}