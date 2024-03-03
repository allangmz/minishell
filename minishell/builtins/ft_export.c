/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkempf-e <tkempf-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:40:27 by aguemazi          #+#    #+#             */
/*   Updated: 2022/12/17 20:36:02 by tkempf-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (!variable)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		variable[i] = str[i];
		i++;
	}
	variable[i] = '\0';
	return (variable);
}

static int	ft_verif_variable(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == -1 && str[i] != '_')
			return (-1);
		i++;
	}
	return (0);
}

void	ft_print_export(char ***env)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		usleep(10);
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd((*env)[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	return ;
}

int	ft_export_variable_env(char ***env, char *str)
{
	char	*variable;
	int		indice_variable;

	if (str == NULL)
	{
		ft_print_export(env);
		return (0);
	}
	variable = ft_variable_extract(str);
	if (variable == NULL)
		return (-1);
	ft_verif_variable(variable);
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
	return (0);
}
