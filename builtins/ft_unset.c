/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:37:43 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/13 19:48:22 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_copy_env_less_var(char ***env, int indice_variable)
{
	char	**env_copy;
	int		i;
	int		j;

	i = 0;
	while ((*env)[i])
		i++;
	env_copy = malloc(sizeof(char *) * (i));
	i = 0;
	while ((*env)[i])
	{
		if (i == indice_variable)
			i++;
		env_copy[i] = malloc(sizeof(char) * (ft_strlen((*env)[i]) + 1));
		j = 0;
		while ((*env)[i][j])
		{
			env_copy[i][j] = (*env)[i][j];
			j++;
		}
		env_copy[i][j] = '\0';
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}

void	ft_unset_variable_env(char ***env, char *variable)
{
	int		indice_variable;
	char	**new_env;

	if (!variable)
	{
		// messafe d'erreur unset: not enough argument
		return ;
	}
	indice_variable = ft_get_indice_variable(*env, variable);
	if (indice_variable == -1)
	{
		return ;
	}
	new_env = ft_copy_env_less_var(env, indice_variable);
	ft_free_doublechar(env);
	*env = new_env;
}