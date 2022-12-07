/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemazi <aguemazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:40:27 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/07 11:30:37 by aguemazi         ###   ########.fr       */
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
		new_env[i++][j] = '\0';
	}
	// new_env[i] = ft_create_str_copy(str, 0);
	new_env[i] = ft_substr(str, 0, ft_strlen(str)); // voir si ça marche
	new_env[++i] = NULL;
	ft_free_doublechar(env);
	*env = new_env;
	return ;
}

void	ft_change_variable_env(char ***env, int indice_var, char *str)
{
	char	*temp;
	int		i;

	temp = malloc(sizeof(char) * ft_strlen(str) + 1);
	i = 0;
	while (str[i])
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = '\0';
	free((*env)[indice_var]);
	(*env)[indice_var] = temp;
	return ;
}

char	*ft_variable_extract(char *str)
{
	char	*variable;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		i++;
	}
	if (!str[i])
		return (NULL);
	variable = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (str[i] != '=')
	{
		variable[i] = str[i];
		i++;
	}
	variable[i] = '\0';
	return (variable);
}

void	ft_export_variable_env(char ***env, char *str)
{
	char	*variable;
	int		indice_variable;

	variable = ft_variable_extract(str);
	// ft_verif_variable(variable); // verifier si contient que alphanum ou _
	indice_variable = ft_get_indice_variable(*env, variable);
	if (indice_variable == -1)
	{
		ft_add_variable_env(env, str);
	}
	else
	{
		ft_change_variable_env(env, indice_variable, str);
	}
	free(variable);
	return ;
}
