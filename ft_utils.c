/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:33:43 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/07 11:34:02 by aguemazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_copy_env(char **env)
{
	char	**env_copy;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		i++;
	}
	env_copy = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		env_copy[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		j = 0;
		while (env[i][j])
		{
			env_copy[i][j] = env[i][j];
			j++;
		}
		env_copy[i][j] = '\0';
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}
