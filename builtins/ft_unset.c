/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:37:43 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/18 20:26:52 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init(int *i, int *tmp)
{
	*i = 0;
	*tmp = 0;
}

char	**ft_copy_env_less_var(char ***env, int indice_variable)
{
	char	**env_copy;
	int		i;
	int		j;
	int		tmp;

	i = 0;
	while ((*env)[i])
		i++;
	env_copy = malloc(sizeof(char *) * (i));
	ft_init(&i, &tmp);
	while ((*env)[i + tmp])
	{
		env_copy[i] = malloc(sizeof(char) * (ft_strlen((*env)[i + tmp]) + 1));
		j = 0;
		while (i != indice_variable && (*env)[i + tmp][j])
		{
			env_copy[i][j] = (*env)[i + tmp][j];
			j++;
		}
		env_copy[i][j] = '\0';
		if (++i == indice_variable)
			tmp = 1;
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
		printf("unset: not enough argument\n");
		return ;
	}
	indice_variable = ft_get_indice_variable(*env, variable);
	if (indice_variable == -1)
		return ;
	new_env = ft_copy_env_less_var(env, indice_variable);
	ft_free_doublechar(env);
	*env = new_env;
}
