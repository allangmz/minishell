/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_variable_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:34:43 by tkempf-e          #+#    #+#             */
/*   Updated: 2022/12/17 20:35:16 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_variable_env(char ***env, char *str)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	while ((*env)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*env)[i])
	{
		new_env[i] = malloc(sizeof(char) * (ft_strlen((*env)[i]) + 1));
		j = 0;
		while ((*env)[i][j])
		{
			new_env[i][j] = (*env)[i][j];
			j++;
		}
		new_env[i][j] = '\0';
		i++;
	}
	new_env[i] = ft_substr(str, 0, ft_strlen(str) + 1);
	new_env[i + 1] = NULL;
	ft_free_doublechar(env);
	*env = new_env;
}
